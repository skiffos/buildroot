// Replacement _Exit that calls the wasivm kernel host import directly.
// Skips atexit handlers per POSIX but must still be vfork-aware.

extern void __posix_exit(int status) __attribute__((noreturn));

void _Exit(int status) {
    __posix_exit(status);
    __builtin_unreachable();
}
