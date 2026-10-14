// ioctl for the WasiVM kernel, which serves the terminal, pseudo-terminal,
// FIONREAD and FIONBIO requests in their Linux values. wasi-libc's ioctl
// serves only FIONREAD and FIONBIO, in values of its own.

#include <stdarg.h>
#include <sys/ioctl.h>

// __wasivm_ioctl performs request req on fd with the pointer or integer arg,
// or sets errno and returns -1.
int __wasivm_ioctl(int fd, int req, void *arg);

int ioctl(int fd, int req, ...)
{
	va_list ap;
	va_start(ap, req);
	void *arg = va_arg(ap, void *);
	va_end(ap);
	return __wasivm_ioctl(fd, req, arg);
}
