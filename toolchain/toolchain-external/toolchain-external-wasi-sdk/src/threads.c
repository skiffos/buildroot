// The C11 mutexes, condition variables and threads, unnamed semaphores and
// pthread_setname_np, which wasi-libc builds only with threads. A WasiVM
// process has one thread: a mutex never contends, thread creation fails so
// callers take their serial path, and a wait that only another thread could
// end reports the deadlock instead of hanging.

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <threads.h>

// mtx_init succeeds; the one thread never contends.
int mtx_init(mtx_t *m, int type)
{
	return thrd_success;
}

// mtx_destroy has nothing to release.
void mtx_destroy(mtx_t *m)
{
}

// mtx_lock succeeds at once.
int mtx_lock(mtx_t *m)
{
	return thrd_success;
}

// mtx_timedlock succeeds at once.
int mtx_timedlock(mtx_t *restrict m, const struct timespec *restrict ts)
{
	return thrd_success;
}

// mtx_trylock succeeds at once.
int mtx_trylock(mtx_t *m)
{
	return thrd_success;
}

// mtx_unlock succeeds at once.
int mtx_unlock(mtx_t *m)
{
	return thrd_success;
}

// cnd_init succeeds; no thread ever waits.
int cnd_init(cnd_t *c)
{
	return thrd_success;
}

// cnd_destroy has nothing to release.
void cnd_destroy(cnd_t *c)
{
}

// cnd_signal has no waiter to wake.
int cnd_signal(cnd_t *c)
{
	return thrd_success;
}

// cnd_broadcast has no waiter to wake.
int cnd_broadcast(cnd_t *c)
{
	return thrd_success;
}

// cnd_wait fails, since no other thread could signal.
int cnd_wait(cnd_t *c, mtx_t *m)
{
	return thrd_error;
}

// cnd_timedwait fails, since no other thread could signal.
int cnd_timedwait(cnd_t *restrict c, mtx_t *restrict m,
		  const struct timespec *restrict ts)
{
	return thrd_error;
}

// thrd_create fails, since the process cannot run a second thread.
int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
	return thrd_error;
}

// thrd_detach fails, since no thread was created.
int thrd_detach(thrd_t thr)
{
	return thrd_error;
}

// thrd_join fails, since no thread was created.
int thrd_join(thrd_t thr, int *res)
{
	return thrd_error;
}

// sem_init sets the count. A shared semaphore would need a second process.
int sem_init(sem_t *sem, int pshared, unsigned value)
{
	if (pshared) {
		errno = ENOSYS;
		return -1;
	}
	sem->__val[0] = value;
	return 0;
}

// sem_destroy has nothing to release.
int sem_destroy(sem_t *sem)
{
	return 0;
}

// sem_getvalue reports the count.
int sem_getvalue(sem_t *restrict sem, int *restrict value)
{
	*value = sem->__val[0];
	return 0;
}

// sem_post raises the count.
int sem_post(sem_t *sem)
{
	sem->__val[0]++;
	return 0;
}

// sem_trywait lowers a positive count and fails with EAGAIN on zero.
int sem_trywait(sem_t *sem)
{
	if (sem->__val[0] <= 0) {
		errno = EAGAIN;
		return -1;
	}
	sem->__val[0]--;
	return 0;
}

// sem_wait lowers a positive count. On zero no other thread could post, so
// it reports the deadlock instead of hanging.
int sem_wait(sem_t *sem)
{
	if (sem->__val[0] <= 0) {
		errno = EDEADLK;
		return -1;
	}
	sem->__val[0]--;
	return 0;
}

// pthread_setname_np accepts the name; the kernel keeps no thread names.
int pthread_setname_np(pthread_t thread, const char *name)
{
	return 0;
}
