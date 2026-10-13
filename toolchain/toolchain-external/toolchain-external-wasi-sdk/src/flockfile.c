#include <stdio.h>

/* A wasivm process has one thread, so its streams need no locks. */

void flockfile(FILE *f)
{
	(void)f;
}

int ftrylockfile(FILE *f)
{
	(void)f;
	return 0;
}

void funlockfile(FILE *f)
{
	(void)f;
}
