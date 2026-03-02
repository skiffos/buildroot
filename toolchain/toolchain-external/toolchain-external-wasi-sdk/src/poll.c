// Replacement poll with POLLPRI handling for WASI.
//
// WASI has no out-of-band data, so POLLPRI can never fire. If all fds
// exclusively request POLLPRI, return ENOSYS since there is nothing
// useful to wait on. Otherwise strip POLLPRI and proceed normally.
//
// Upstream fix: https://github.com/WebAssembly/wasi-libc/pull/754

#include <errno.h>
#include <poll.h>
#include <stdbool.h>
#include <wasi/api.h>

// POLLPRI is not in wasi-libc headers (no OOB data in WASI).
#ifndef POLLPRI
#define POLLPRI 0x0200
#endif

int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    size_t maxevents = 2 * nfds + 1;
    __wasi_subscription_t subscriptions[maxevents];
    size_t nsubscriptions = 0;

    // Check if POLLPRI is the only event requested across all fds.
    {
        bool has_pri_only = false;
        bool has_non_pri = false;
        for (size_t i = 0; i < nfds; ++i) {
            if (fds[i].fd < 0 || fds[i].events == 0)
                continue;
            if (fds[i].events & ~POLLPRI)
                has_non_pri = true;
            else
                has_pri_only = true;
        }
        if (has_pri_only && !has_non_pri) {
            errno = ENOSYS;
            return -1;
        }
    }

    for (size_t i = 0; i < nfds; ++i) {
        struct pollfd *pollfd = &fds[i];
        if (pollfd->fd < 0)
            continue;
        // Strip POLLPRI; it is never reported in WASI.
        short events = pollfd->events & ~POLLPRI;
        bool created_events = false;
        if ((events & POLLRDNORM) != 0) {
            __wasi_subscription_t *s = &subscriptions[nsubscriptions++];
            *s = (__wasi_subscription_t){
                .userdata = (uintptr_t)pollfd,
                .u.tag = __WASI_EVENTTYPE_FD_READ,
                .u.u.fd_read.file_descriptor = pollfd->fd,
            };
            created_events = true;
        }
        if ((events & POLLWRNORM) != 0) {
            __wasi_subscription_t *s = &subscriptions[nsubscriptions++];
            *s = (__wasi_subscription_t){
                .userdata = (uintptr_t)pollfd,
                .u.tag = __WASI_EVENTTYPE_FD_WRITE,
                .u.u.fd_write.file_descriptor = pollfd->fd,
            };
            created_events = true;
        }
        // Entries with only POLLPRI (stripped above) produce no
        // subscriptions; skip them silently.
        if (!created_events && events != 0) {
            errno = ENOSYS;
            return -1;
        }
    }

    if (timeout >= 0) {
        __wasi_subscription_t *s = &subscriptions[nsubscriptions++];
        *s = (__wasi_subscription_t){
            .u.tag = __WASI_EVENTTYPE_CLOCK,
            .u.u.clock.id = __WASI_CLOCKID_REALTIME,
            .u.u.clock.timeout = (__wasi_timestamp_t)timeout * 1000000,
        };
    }

    size_t nevents;
    __wasi_event_t events[nsubscriptions];
    __wasi_errno_t error =
        __wasi_poll_oneoff(subscriptions, events, nsubscriptions, &nevents);
    if (error != 0) {
        if (nsubscriptions == 0)
            errno = ENOTSUP;
        else
            errno = error;
        return -1;
    }

    for (size_t i = 0; i < nfds; ++i)
        fds[i].revents = 0;

    for (size_t i = 0; i < nevents; ++i) {
        const __wasi_event_t *event = &events[i];
        if (event->type == __WASI_EVENTTYPE_FD_READ ||
            event->type == __WASI_EVENTTYPE_FD_WRITE) {
            struct pollfd *pollfd =
                (struct pollfd *)(uintptr_t)event->userdata;
            if (event->error == __WASI_ERRNO_BADF)
                pollfd->revents |= POLLNVAL;
            else if (event->error == __WASI_ERRNO_PIPE)
                pollfd->revents |= POLLHUP;
            else if (event->error != 0)
                pollfd->revents |= POLLERR;
            else {
                if (event->type == __WASI_EVENTTYPE_FD_READ) {
                    pollfd->revents |= POLLRDNORM;
                    if (event->fd_readwrite.flags &
                        __WASI_EVENTRWFLAGS_FD_READWRITE_HANGUP)
                        pollfd->revents |= POLLHUP;
                } else {
                    pollfd->revents |= POLLWRNORM;
                    if (event->fd_readwrite.flags &
                        __WASI_EVENTRWFLAGS_FD_READWRITE_HANGUP)
                        pollfd->revents |= POLLHUP;
                }
            }
        }
    }

    int retval = 0;
    for (size_t i = 0; i < nfds; ++i) {
        if ((fds[i].revents & POLLHUP) != 0)
            fds[i].revents &= ~POLLWRNORM;
        if (fds[i].revents != 0)
            ++retval;
    }
    return retval;
}
