// pthread_sigmask, which wasi-libc builds only with threads. A WasiVM
// process has one thread, so it is sigprocmask returning the error number,
// as in musl.

#include <errno.h>
#include <signal.h>

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
	return sigprocmask(how, set, old) ? errno : 0;
}
