// Replacement exit that flushes stdio then calls the wasivm kernel
// host import. wasi-libc's exit calls __wasi_proc_exit directly,
// bypassing the kernel's vfork-aware exit handling.

typedef struct __FILE FILE;
extern int fflush(FILE *);
extern void __posix_exit(int status) __attribute__((noreturn));

void exit(int status) {
    fflush((FILE *)0);
    __posix_exit(status);
    __builtin_unreachable();
}
