#ifndef _SYS_TIMERFD_H
#define _SYS_TIMERFD_H
#include <time.h>
#define TFD_CLOEXEC  02000000
#define TFD_NONBLOCK 04000
#define TFD_TIMER_ABSTIME 1
int timerfd_create(int clockid, int flags);
int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);
int timerfd_gettime(int fd, struct itimerspec *curr_value);
#endif
