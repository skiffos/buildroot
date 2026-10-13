// The utmpx functions, which wasi-libc lacks. As in musl, no login records
// are kept: the database is always empty and writes are dropped.

#include <stddef.h>
#include <utmpx.h>

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
