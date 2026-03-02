#ifndef __ASSEMBLER__
/* POSIX compatibility layer for wasi-libc.
 *
 * Force-included via -include in the toolchain wrapper. Provides
 * constants, structs, and function declarations that wasi-libc
 * deliberately omits (guarded behind __wasilibc_unmodified_upstream).
 *
 * These are stub declarations -- the wasivm Go kernel handles the
 * actual implementation at runtime via WASI host imports.
 */
#ifndef _WASI_POSIX_FIXUPS_H
#define _WASI_POSIX_FIXUPS_H

/* Suppress setjmp.h error - we provide stub setjmp/longjmp via --import-undefined */
#ifndef __wasm_exception_handling__
#define __wasm_exception_handling__ 1
#endif

#include <sys/types.h>
#include <stddef.h>

/* ================================================================
 * Socket types and address families
 * ================================================================ */

#ifndef SOCK_RAW
#define SOCK_RAW       3
#endif
#ifndef SOCK_RDM
#define SOCK_RDM       4
#endif
/* wasi-libc uses SOCK_DGRAM=5, so SOCK_SEQPACKET must differ. */
#ifndef SOCK_SEQPACKET
#define SOCK_SEQPACKET 105
#endif
#ifndef SOCK_PACKET
#define SOCK_PACKET    10
#endif

#ifndef SHUT_RD
#define SHUT_RD   0
#define SHUT_WR   1
#define SHUT_RDWR 2
#endif

#ifndef PF_PACKET
#define PF_PACKET  17
#define AF_PACKET  PF_PACKET
#endif
#ifndef PF_NETLINK
#define PF_NETLINK 16
#define AF_NETLINK PF_NETLINK
#endif

/* Override wasi-libc truncated sockaddr_un (no sun_path). */
#define __wasilibc___struct_sockaddr_un_h
#include <__typedef_sa_family_t.h>
struct sockaddr_un {
    sa_family_t sun_family;
    char sun_path[108];
};

#ifndef SO_DEBUG
#define SO_DEBUG        1
#define SO_REUSEADDR    2
#define SO_TYPE         3
#define SO_ERROR        4
#define SO_DONTROUTE    5
#define SO_BROADCAST    6
#define SO_SNDBUF       7
#define SO_RCVBUF       8
#define SO_KEEPALIVE    9
#define SO_OOBINLINE    10
#define SO_RCVBUFFORCE  33
#define SO_SNDBUFFORCE  32
#endif

#ifndef SOL_PACKET
#define SOL_PACKET 263
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0x40
#endif

#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#define NI_NUMERICSERV 2
#define NI_NOFQDN      4
#define NI_NAMEREQD    8
#define NI_DGRAM       16
#endif

/* ================================================================
 * Signals
 * ================================================================ */

#include <signal.h>

#ifndef SA_RESTART
#define SA_RESTART   0x10000000
#define SA_NODEFER   0x40000000
#define SA_RESETHAND 0x80000000
#define SA_NOCLDSTOP 1
#define SA_NOCLDWAIT 2
#define SA_SIGINFO   4
#define SA_ONSTACK   0x08000000
#endif

#ifndef SIG_BLOCK
#define SIG_BLOCK   0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#endif

#ifndef _WASI_SIGACTION_DEFINED
#define _WASI_SIGACTION_DEFINED
struct sigaction {
    void (*sa_handler)(int);
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    sigset_t sa_mask;
};
#endif

#ifndef WCOREDUMP
#define WCOREDUMP(s) ((s) & 0x80)
#endif
int killpg(pid_t, int);
int sigaction(int, const struct sigaction *, struct sigaction *);
int sigaddset(sigset_t *, int);
int sigdelset(sigset_t *, int);
int sigfillset(sigset_t *);
int sigemptyset(sigset_t *);
int sigismember(const sigset_t *, int);
int sigisemptyset(const sigset_t *);
int sigprocmask(int, const sigset_t *, sigset_t *);
int sigtimedwait(const sigset_t *, void *, const struct timespec *);
int sigwait(const sigset_t *, int *);
int sigsuspend(const sigset_t *);

#ifndef _WASI_SIGALTSTACK_DEFINED
#define _WASI_SIGALTSTACK_DEFINED
typedef struct sigaltstack {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
} stack_t;
#endif
int sigaltstack(const stack_t *, stack_t *);
int sigpending(sigset_t *);

#ifndef ITIMER_REAL
#define ITIMER_REAL    0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF    2
struct itimerval {
    struct timeval it_interval;
    struct timeval it_value;
};
int setitimer(int, const struct itimerval *, struct itimerval *);
int getitimer(int, struct itimerval *);
#endif

/* ================================================================
 * Process management
 * ================================================================ */

pid_t fork(void);
pid_t vfork(void);
pid_t setsid(void);
pid_t getsid(pid_t);
pid_t getppid(void);
pid_t getpgid(pid_t);
pid_t getpgrp(void);
int setpgid(pid_t, pid_t);
int setpgrp(void);
int kill(pid_t, int);
pid_t waitpid(pid_t, int *, int);
pid_t wait(int *);
void _exit(int) __attribute__((noreturn));

int execv(const char *, char *const[]);
int execve(const char *, char *const[], char *const[]);
int execvp(const char *, char *const[]);
int execl(const char *, const char *, ...);
int execle(const char *, const char *, ...);
int execlp(const char *, const char *, ...);

/* Wait status macros */
#ifndef WIFEXITED
#define WIFEXITED(s)   (((s) & 0x7f) == 0)
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WIFSIGNALED(s) (((signed char)(((s) & 0x7f) + 1) >> 1) > 0)
#define WTERMSIG(s)    ((s) & 0x7f)
#define WIFSTOPPED(s)  (((s) & 0xff) == 0x7f)
#define WSTOPSIG(s)    WEXITSTATUS(s)
#endif

/* ================================================================
 * User/group IDs
 * ================================================================ */

uid_t getuid(void);
gid_t getgid(void);
uid_t geteuid(void);
gid_t getegid(void);
int setuid(uid_t);
int setgid(gid_t);
int seteuid(uid_t);
int setegid(gid_t);
int setreuid(uid_t, uid_t);
int setregid(gid_t, gid_t);
int getresuid(uid_t *, uid_t *, uid_t *);
int getresgid(gid_t *, gid_t *, gid_t *);
int setresuid(uid_t, uid_t, uid_t);
int setresgid(gid_t, gid_t, gid_t);
int getgroups(int, gid_t[]);
int setgroups(size_t, const gid_t *);
int initgroups(const char *, gid_t);

/* ================================================================
 * File operations
 * ================================================================ */

int chown(const char *, uid_t, gid_t);
int lchown(const char *, uid_t, gid_t);
int fchown(int, uid_t, gid_t);
mode_t umask(mode_t);
int mknod(const char *, mode_t, dev_t);
int mkfifo(const char *, mode_t);
int chroot(const char *);
void sync(void);
int link(const char *, const char *);
int symlink(const char *, const char *);
ssize_t readlink(const char *, char *, size_t);
int truncate(const char *, off_t);
int ftruncate(int, off_t);
int access(const char *, int);
int chdir(const char *);
int fchdir(int);
char *getcwd(char *, size_t);
long pathconf(const char *, int);
long fpathconf(int, int);

/* Pipe/dup */
int pipe(int[2]);
int pipe2(int[2], int);
int dup(int);
int dup2(int, int);
int dup3(int, int, int);

/* Override wasi-libc fcntl (returns EINVAL for F_DUPFD) with host import. */
int __posix_fcntl3(int, int, int);

#ifndef O_NDELAY
#define O_NDELAY O_NONBLOCK
#endif

/* File locking (wasi-libc omits all of these) */
#ifndef F_RDLCK
#define F_RDLCK  0
#define F_WRLCK  1
#define F_UNLCK  2
#endif
#ifndef F_DUPFD
#define F_DUPFD         0
#define F_DUPFD_CLOEXEC 1030
#endif
#ifndef F_GETLK
#define F_GETLK  5
#define F_SETLK  6
#define F_SETLKW 7
#endif

/* ================================================================
 * Terminal
 * ================================================================ */

#ifndef TIOCSCTTY
#define TIOCSCTTY  0x540E
#define TIOCNOTTY  0x5422
#define TIOCGPGRP  0x540F
#define TIOCSPGRP  0x5410
#define TIOCGWINSZ 0x5413
#define TIOCSWINSZ 0x5414
#endif
#ifndef TIOCSTI
#define TIOCSTI    0x5412
#endif
#ifndef TIOCSSERIAL
#define TIOCSSERIAL  0x541F
#define TIOCGSERIAL  0x541E
#define TIOCSERCONFIG 0x5453
#endif

#ifndef _WASI_WINSIZE_DEFINED
#define _WASI_WINSIZE_DEFINED
#define __NEED_struct_winsize
#include <bits/alltypes.h>
#endif

pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);
char *ttyname(int);
int ttyname_r(int, char *, size_t);
int isatty(int);

/* PTY */
int grantpt(int);
int unlockpt(int);
int ptsname_r(int, char *, size_t);

/* ================================================================
 * Network
 * ================================================================ */

struct sockaddr;
struct iovec;

int socket(int, int, int);
int bind(int, const struct sockaddr *, unsigned int);
int connect(int, const struct sockaddr *, unsigned int);
int listen(int, int);
int accept(int, struct sockaddr *, unsigned int *);
ssize_t send(int, const void *, size_t, int);
ssize_t recv(int, void *, size_t, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, unsigned int);
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *, unsigned int *);
ssize_t sendmsg(int, const struct msghdr *, int);
ssize_t recvmsg(int, struct msghdr *, int);
int setsockopt(int, int, int, const void *, unsigned int);
int getsockopt(int, int, int, void *, unsigned int *);
int shutdown(int, int);
int getsockname(int, struct sockaddr *, unsigned int *);
int getpeername(int, struct sockaddr *, unsigned int *);
int sethostname(const char *, size_t);
int gethostname(char *, size_t);

/* CMSG macros (struct msghdr from wasi-libc __struct_msghdr.h) */
struct cmsghdr {
    unsigned int cmsg_len;
    int cmsg_level;
    int cmsg_type;
};

#ifndef CMSG_ALIGN
#define CMSG_ALIGN(len) (((len) + sizeof(long) - 1) & ~(sizeof(long) - 1))
#define CMSG_LEN(len)   (CMSG_ALIGN(sizeof(struct cmsghdr)) + (len))
#define CMSG_SPACE(len)  (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))
#define CMSG_DATA(cmsg)  ((unsigned char *)((struct cmsghdr *)(cmsg) + 1))
#define CMSG_FIRSTHDR(mhdr) \
    ((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? \
     (struct cmsghdr *)(mhdr)->msg_control : (struct cmsghdr *)0)
#define CMSG_NXTHDR(mhdr, cmsg) \
    ((cmsg)->cmsg_len < sizeof(struct cmsghdr) ? (struct cmsghdr *)0 : \
     ((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len) + \
      sizeof(struct cmsghdr) > \
      (unsigned char *)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
     (struct cmsghdr *)0 : \
     (struct cmsghdr *)((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len)))
#endif

/* ================================================================
 * Resource limits and priority
 * ================================================================ */

#ifndef RLIMIT_CORE
typedef unsigned long rlim_t;
#define RLIM_INFINITY (~(rlim_t)0)
struct rlimit {
    rlim_t rlim_cur;
    rlim_t rlim_max;
};
#define RLIMIT_FSIZE   1
#define RLIMIT_DATA    2
#define RLIMIT_STACK   3
#define RLIMIT_CORE    4
#define RLIMIT_RSS     5
#define RLIMIT_NPROC   6
#define RLIMIT_NOFILE  7
#define RLIMIT_AS      9
int getrlimit(int, struct rlimit *);
int setrlimit(int, const struct rlimit *);
#endif

#ifndef PRIO_PROCESS
#define PRIO_PROCESS 0
#define PRIO_PGRP    1
#define PRIO_USER    2
#endif

int getpriority(int, id_t);
int setpriority(int, id_t, int);
int nice(int);

/* ================================================================
 * Clock and time
 * ================================================================ */

#include <time.h>

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME  0
#define CLOCK_MONOTONIC 1
#endif
#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME         ((clockid_t)7)
#define CLOCK_REALTIME_COARSE  ((clockid_t)5)
#define CLOCK_MONOTONIC_COARSE ((clockid_t)6)
#endif

int clock_settime(clockid_t, const struct timespec *);
void tzset(void);

struct timeval;
int settimeofday(const struct timeval *, const void *);
int gettimeofday(struct timeval *, void *);
unsigned int alarm(unsigned int);
int pause(void);

/* ================================================================
 * Syslog
 * ================================================================ */

#ifndef LOG_AUTH
#define LOG_AUTH     (4<<3)
#define LOG_AUTHPRIV (10<<3)
#define LOG_CONS     0x02
#endif

/* ================================================================
 * CPU affinity
 * ================================================================ */

#ifndef CPU_SETSIZE
#define CPU_SETSIZE 1024
typedef struct {
    unsigned long __bits[CPU_SETSIZE / (8 * sizeof(unsigned long))];
} cpu_set_t;
int sched_getaffinity(pid_t, size_t, cpu_set_t *);
int sched_setaffinity(pid_t, size_t, const cpu_set_t *);
#endif

/* ================================================================
 * Sysconf
 * ================================================================ */

long sysconf(int);

#ifndef _SC_CLK_TCK
#define _SC_CLK_TCK          2
#define _SC_OPEN_MAX         4
#define _SC_PAGESIZE         30
#define _SC_PAGE_SIZE        _SC_PAGESIZE
#define _SC_NPROCESSORS_CONF 83
#define _SC_NPROCESSORS_ONLN 84
#define _SC_PHYS_PAGES       85
#endif

/* ================================================================
 * Block device and ioctl
 * ================================================================ */

#ifndef BLKFLSBUF
#define BLKFLSBUF    0x1261
#define BLKGETSIZE   0x1260
#define BLKGETSIZE64 0x80081272
#endif

#ifndef _IO
#define _IO(type,nr)        ((type)<<8|(nr))
#define _IOR(type,nr,size)  _IO(type,nr)
#define _IOW(type,nr,size)  _IO(type,nr)
#define _IOWR(type,nr,size) _IO(type,nr)
#endif

/* ================================================================
 * Misc
 * ================================================================ */

struct spwd;
int getspnam_r(const char *, struct spwd *, char *, size_t, struct spwd **);

int mkstemp(char *);
int mkostemp(char *, int);
int mkstemps(char *, int);
char *mkdtemp(char *);

#ifndef TP_STATUS_CSUMNOTREADY
#define TP_STATUS_CSUMNOTREADY (1 << 3)
#endif

#endif /* _WASI_POSIX_FIXUPS_H */
#endif /* \!__ASSEMBLER__ */
