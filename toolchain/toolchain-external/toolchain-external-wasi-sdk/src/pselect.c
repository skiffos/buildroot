// Replacement pselect that threads errorfds through poll as POLLPRI.
//
// WASI has no out-of-band data, so POLLPRI never fires. But pselect
// should not fail when errorfds is provided alongside other fd sets.
// errorfds entries become POLLPRI poll requests; poll() strips POLLPRI
// when other events are present, returns ENOSYS when POLLPRI-only.
//
// Uses inline timeout conversion to avoid internal wasi-libc headers.
//
// Upstream fix: https://github.com/WebAssembly/wasi-libc/pull/754

#include <sys/select.h>
#include <errno.h>
#include <limits.h>
#include <poll.h>
#include <stddef.h>

#ifndef POLLPRI
#define POLLPRI 0x0200
#endif

int pselect(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
            fd_set *restrict errorfds, const struct timespec *restrict timeout,
            const sigset_t *sigmask) {
    if (nfds < 0) {
        errno = EINVAL;
        return -1;
    }

    fd_set empty;
    FD_ZERO(&empty);
    if (readfds == NULL)
        readfds = &empty;
    if (writefds == NULL)
        writefds = &empty;
    if (errorfds == NULL)
        errorfds = &empty;

    struct pollfd pfds[readfds->__nfds + writefds->__nfds + errorfds->__nfds];
    size_t npfds = 0;

    for (size_t i = 0; i < readfds->__nfds; ++i) {
        int fd = readfds->__fds[i];
        if (fd < nfds) {
            pfds[npfds].fd = fd;
            pfds[npfds].events = POLLRDNORM;
            pfds[npfds].revents = 0;
            npfds++;
        }
    }
    size_t read_count = npfds;

    for (size_t i = 0; i < writefds->__nfds; ++i) {
        int fd = writefds->__fds[i];
        if (fd < nfds) {
            pfds[npfds].fd = fd;
            pfds[npfds].events = POLLWRNORM;
            pfds[npfds].revents = 0;
            npfds++;
        }
    }
    size_t write_end = npfds;

    for (size_t i = 0; i < errorfds->__nfds; ++i) {
        int fd = errorfds->__fds[i];
        if (fd < nfds) {
            pfds[npfds].fd = fd;
            pfds[npfds].events = POLLPRI;
            pfds[npfds].revents = 0;
            npfds++;
        }
    }

    int poll_timeout;
    if (timeout) {
        long long ns =
            (long long)timeout->tv_sec * 1000000000LL + timeout->tv_nsec;
        if (ns < 0) {
            errno = EINVAL;
            return -1;
        }
        long long ms = ns / 1000000;
        poll_timeout = (ms > INT_MAX) ? INT_MAX : (int)ms;
    } else {
        poll_timeout = -1;
    }

    if (poll(pfds, npfds, poll_timeout) < 0)
        return -1;

    FD_ZERO(readfds);
    FD_ZERO(writefds);
    FD_ZERO(errorfds);
    for (size_t i = 0; i < npfds; ++i) {
        struct pollfd *pfd = pfds + i;
        if (i < read_count) {
            if ((pfd->revents & (POLLRDNORM | POLLIN | POLLHUP | POLLERR)) != 0)
                readfds->__fds[readfds->__nfds++] = pfd->fd;
        } else if (i < write_end) {
            if ((pfd->revents & (POLLWRNORM | POLLOUT | POLLERR)) != 0)
                writefds->__fds[writefds->__nfds++] = pfd->fd;
        } else {
            if ((pfd->revents & POLLPRI) != 0)
                errorfds->__fds[errorfds->__nfds++] = pfd->fd;
        }
    }

    return readfds->__nfds + writefds->__nfds + errorfds->__nfds;
}
