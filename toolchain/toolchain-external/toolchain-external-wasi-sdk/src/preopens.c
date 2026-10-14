// Path lookup for the WasiVM kernel, replacing wasi-libc's preopen table.
//
// wasi-libc maps each path to a preopened directory descriptor and a path
// relative to it. The WasiVM kernel resolves paths as Linux does, an absolute
// path from the root and a relative one from the working directory chdir
// sets, and preopens no directory, so every descriptor from 3 up belongs to
// the program. Each path goes to the kernel unchanged under AT_FDCWD.

#include <fcntl.h>
#include <stddef.h>
#include <wasi/libc-find-relpath.h>

int __wasilibc_find_relpath(const char *path, const char **abs_prefix,
                            char **relative_path, size_t relative_path_len) {
  (void)relative_path_len;
  *abs_prefix = "";
  *relative_path = (char *)path;
  return AT_FDCWD;
}
