// getcwd for the WasiVM kernel, after musl.
//
// The kernel owns the working directory: chdir and fchdir change it there, and
// a child inherits it across fork and exec. wasi-libc's getcwd reports its own
// copy, which none of these update, so this one asks the kernel.

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

// __wasivm_getcwd writes the working directory and its NUL to buf and returns
// their length, or sets errno and returns -1.
int __wasivm_getcwd(char *buf, size_t size);

char *getcwd(char *buf, size_t size) {
  char tmp[buf ? 1 : PATH_MAX];
  if (!buf) {
    buf = tmp;
    size = sizeof tmp;
  } else if (!size) {
    errno = EINVAL;
    return 0;
  }
  if (__wasivm_getcwd(buf, size) < 0)
    return 0;
  return buf == tmp ? strdup(buf) : buf;
}
