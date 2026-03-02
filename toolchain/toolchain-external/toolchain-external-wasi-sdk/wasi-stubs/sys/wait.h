#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H
#include <sys/types.h>
#define WNOHANG 1
#define WUNTRACED 2
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WTERMSIG(s) ((s) & 0x7f)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSIGNALED(s) (((signed char)(((s)&0x7f)+1)>>1) > 0)
#define WIFSTOPPED(s) ((short)((((s)&0xffff)*0x10001U)>>8) > 0x7f00)
typedef int idtype_t;
pid_t wait(int *);
pid_t waitpid(pid_t, int *, int);
#endif
