// Replacement fcntl that forwards to the wasivm kernel host import.
// wasi-libc's fcntl only handles F_GETFL/F_SETFL and returns EINVAL
// for F_DUPFD and others needed by busybox job control.

#include <stdarg.h>

extern int __posix_fcntl3(int fd, int cmd, int arg);

int fcntl(int fd, int cmd, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, cmd);
    int arg = __builtin_va_arg(ap, int);
    __builtin_va_end(ap);
    return __posix_fcntl3(fd, cmd, arg);
}
