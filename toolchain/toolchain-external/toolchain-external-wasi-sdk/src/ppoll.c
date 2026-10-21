// ppoll, which wasi-libc lacks, over poll and sigprocmask. A process has one
// thread, so swapping the signal mask around poll differs from an atomic
// ppoll only for a signal that arrives between the two calls.

#include <limits.h>
#include <poll.h>
#include <signal.h>
#include <time.h>

int ppoll(struct pollfd *fds, nfds_t n, const struct timespec *to, const sigset_t *mask)
{
	int timeout = -1, ret;
	sigset_t old;

	if (to) {
		long long ms = to->tv_sec * 1000LL + (to->tv_nsec + 999999) / 1000000;
		timeout = ms > INT_MAX ? INT_MAX : (int)ms;
	}
	if (mask) sigprocmask(SIG_SETMASK, mask, &old);
	ret = poll(fds, n, timeout);
	if (mask) sigprocmask(SIG_SETMASK, &old, 0);
	return ret;
}
