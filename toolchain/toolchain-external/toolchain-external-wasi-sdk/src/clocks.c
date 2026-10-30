// The Linux clocks wasi-libc does not name. A clockid_t points at a clock
// object holding the clock number clock_gettime passes to the kernel, which
// numbers its clocks as Linux does.

#include <time.h>
#include <wasi/api.h>

struct __clockid {
	__wasi_clockid_t id;
};

const struct __clockid _CLOCK_PROCESS_CPUTIME_ID = { 2 };
const struct __clockid _CLOCK_THREAD_CPUTIME_ID = { 3 };
const struct __clockid _CLOCK_MONOTONIC_RAW = { 4 };
const struct __clockid _CLOCK_REALTIME_COARSE = { 5 };
const struct __clockid _CLOCK_MONOTONIC_COARSE = { 6 };
const struct __clockid _CLOCK_BOOTTIME = { 7 };
