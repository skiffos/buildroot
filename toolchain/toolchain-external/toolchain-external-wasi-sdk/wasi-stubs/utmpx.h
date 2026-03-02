#ifndef _UTMPX_H
#define _UTMPX_H
#include <sys/types.h>
#include <sys/time.h>
#define EMPTY         0
#define RUN_LVL       1
#define BOOT_TIME     2
#define NEW_TIME      3
#define OLD_TIME      4
#define INIT_PROCESS  5
#define LOGIN_PROCESS 6
#define USER_PROCESS  7
#define DEAD_PROCESS  8
struct utmpx { short ut_type; pid_t ut_pid; char ut_line[32]; char ut_id[4]; char ut_user[32]; char ut_host[256]; struct { short e_termination; short e_exit; } ut_exit; long ut_session; struct timeval ut_tv; int ut_addr_v6[4]; char __unused[20]; };
void setutxent(void);
void endutxent(void);
struct utmpx *getutxent(void);
struct utmpx *getutxid(const struct utmpx *ut);
struct utmpx *getutxline(const struct utmpx *ut);
struct utmpx *pututxline(const struct utmpx *ut);
void updwtmpx(const char *file, const struct utmpx *ut);
#endif
