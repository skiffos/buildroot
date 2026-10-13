
/* wasi-libc's chmod family fails with ENOSYS. The wasivm kernel sets file
 * modes, so route the calls to its imports. */
#define chmod __posix_chmod
#define fchmod __posix_fchmod
#define fchmodat __posix_fchmodat
int chmod(const char *, mode_t);
int fchmod(int, mode_t);
int fchmodat(int, const char *, mode_t, int);
