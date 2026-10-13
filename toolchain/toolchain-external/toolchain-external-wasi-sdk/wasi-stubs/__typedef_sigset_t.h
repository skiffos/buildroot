#ifndef __wasilibc___typedef_sigset_t_h
#define __wasilibc___typedef_sigset_t_h

/* sigset_t holds 64 signals, one bit each, as the wasivm kernel reads and
 * writes it. wasi-libc's one-byte placeholder is too small for the kernel's
 * sigemptyset and sigaction. */
typedef unsigned long long sigset_t;

#endif
