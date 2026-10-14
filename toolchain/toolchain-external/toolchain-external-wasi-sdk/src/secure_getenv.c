// secure_getenv, which wasi-libc declares but does not build. musl returns
// null only in a setuid program, and no WasiVM program runs setuid.

#define _GNU_SOURCE
#include <stdlib.h>

char *secure_getenv(const char *name)
{
	return getenv(name);
}
