
/* wasi-libc declares a two-argument opendirat. Packages such as gnulib
 * define their own, so rename wasi-libc's out of their way. */
#define opendirat __wasilibc_opendirat
