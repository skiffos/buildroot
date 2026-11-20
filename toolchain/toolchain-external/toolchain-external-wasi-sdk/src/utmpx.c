// The utmpx functions and their utmp names, which wasi-libc lacks. As in
// musl, no login records are kept: the database is always empty and writes
// are dropped.

#include <errno.h>
#include <stddef.h>
#include <utmp.h>

void setutxent(void)
{
}

void endutxent(void)
{
}

struct utmpx *getutxent(void)
{
	return NULL;
}

struct utmpx *getutxid(const struct utmpx *ut)
{
	return NULL;
}

struct utmpx *getutxline(const struct utmpx *ut)
{
	return NULL;
}

struct utmpx *pututxline(const struct utmpx *ut)
{
	return NULL;
}

void updwtmpx(const char *file, const struct utmpx *ut)
{
}

void setutent(void) __attribute__((alias("setutxent")));
void endutent(void) __attribute__((alias("endutxent")));
struct utmp *getutent(void) __attribute__((alias("getutxent")));
struct utmp *getutid(const struct utmp *) __attribute__((alias("getutxid")));
struct utmp *getutline(const struct utmp *) __attribute__((alias("getutxline")));
struct utmp *pututline(const struct utmp *) __attribute__((alias("pututxline")));
void updwtmp(const char *, const struct utmp *) __attribute__((alias("updwtmpx")));

int utmpname(const char *file)
{
	if (file) {
		errno = ENOTSUP;
		return -1;
	}
	return 0;
}
