// Replacement exit that runs the cleanup hooks and then calls the wasivm
// kernel's exit, which handles the process table; wasi-libc's exit calls
// __wasi_proc_exit directly. _start calls __wasm_call_dtors when main
// returns, so this object defines it as wasi-libc's exit.c does.

#include <stdlib.h>

extern void __posix_exit(int status) __attribute__((noreturn));

static void dummy(void)
{
}

// atexit.c and __stdio_exit.c override these.
extern __typeof(dummy) __funcs_on_exit __attribute__((weak, alias("dummy")));
extern __typeof(dummy) __stdio_exit __attribute__((weak, alias("dummy")));

void __wasm_call_dtors(void)
{
	__funcs_on_exit();
	__stdio_exit();
}

_Noreturn void exit(int status)
{
	__wasm_call_dtors();
	__posix_exit(status);
}
