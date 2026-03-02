#ifndef __ASSEMBLER__
/* Supplement wasi-libc with POSIX constants and declarations it omits.
 * These are stub declarations -- the wasivm kernel handles them at runtime.
 * Force-included via -include in the toolchain wrapper. */
#ifndef _WASI_POSIX_FIXUPS_H
#define _WASI_POSIX_FIXUPS_H

#include <sys/types.h>
#include <stddef.h>

/* Socket types omitted by wasi-libc */
#ifndef SOCK_RAW
#define SOCK_RAW       3
#endif
#ifndef SOCK_RDM
#define SOCK_RDM       4
#endif
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
#define PF_PACKET 17
#define AF_PACKET PF_PACKET
#endif
#ifndef PF_NETLINK
#define PF_NETLINK 16
#define AF_NETLINK PF_NETLINK
#endif

/* ---- Signal types and constants ---- */
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

/* sigaction struct - wasi-libc guards this behind __wasilibc_unmodified_upstream */
#ifndef _WASI_SIGACTION_DEFINED
#define _WASI_SIGACTION_DEFINED
struct sigaction {
    void (*sa_handler)(int);
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    sigset_t sa_mask;
};
#endif

int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigfillset(sigset_t *set);
int sigemptyset(sigset_t *set);
int sigismember(const sigset_t *set, int signum);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigtimedwait(const sigset_t *set, void *info, const struct timespec *timeout);
int sigwait(const sigset_t *set, int *sig);
int sigsuspend(const sigset_t *mask);

/* Process priority */
#ifndef PRIO_PROCESS
#define PRIO_PROCESS 0
#define PRIO_PGRP    1
#define PRIO_USER    2
#endif

/* Resource limits */
#ifndef RLIMIT_CORE
typedef unsigned long rlim_t;
#define RLIM_INFINITY (~(rlim_t)0)
struct rlimit {
    rlim_t rlim_cur;
    rlim_t rlim_max;
};
#define RLIMIT_CORE    4
#define RLIMIT_NOFILE  7
#define RLIMIT_NPROC   6
#define RLIMIT_AS      9
#define RLIMIT_FSIZE   1
#define RLIMIT_DATA    2
#define RLIMIT_STACK   3
#define RLIMIT_RSS     5
int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
#endif

/* Terminal ioctl constants */
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

/* struct winsize - wasi-libc has it in bits/alltypes.h but gated */
#ifndef _WASI_WINSIZE_DEFINED
#define _WASI_WINSIZE_DEFINED
#define __NEED_struct_winsize
#include <bits/alltypes.h>
#endif

/* Syslog constants missing from stub */
#ifndef LOG_AUTH
#define LOG_AUTH    (4<<3)
#define LOG_AUTHPRIV (10<<3)
#define LOG_CONS   0x02
#endif

/* CPU affinity */
#ifndef CPU_SETSIZE
#define CPU_SETSIZE 1024
typedef struct { unsigned long __bits[CPU_SETSIZE / (8 * sizeof(unsigned long))]; } cpu_set_t;
int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
int sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask);
#endif

/* ---- POSIX function declarations missing from wasi-libc ---- */

/* Process management */
pid_t fork(void);
pid_t vfork(void);
pid_t setsid(void);
pid_t getsid(pid_t pid);
int execvp(const char *file, char *const argv[]);
int execlp(const char *file, const char *arg, ...);
int execv(const char *path, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
int execl(const char *path, const char *arg, ...);
int kill(pid_t pid, int sig);
pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait(int *status);
void _exit(int status) __attribute__((noreturn));

/* File ownership */
int chown(const char *path, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);

/* File creation */
mode_t umask(mode_t mask);
int mknod(const char *path, mode_t mode, dev_t dev);
int mkfifo(const char *path, mode_t mode);

/* Filesystem */
int chroot(const char *path);
void sync(void);

/* Clock */
#include <time.h>
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME  0
#define CLOCK_MONOTONIC 1
#endif
#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME  ((clockid_t)7)
#define CLOCK_REALTIME_COARSE ((clockid_t)5)
#define CLOCK_MONOTONIC_COARSE ((clockid_t)6)
#endif
int clock_settime(clockid_t clk_id, const struct timespec *tp);

/* Priority */
int getpriority(int which, id_t who);
int setpriority(int which, id_t who, int prio);

/* Groups */
int setgroups(size_t size, const gid_t *list);
int initgroups(const char *user, gid_t group);

/* Pipe */
int pipe(int pipefd[2]);
int pipe2(int pipefd[2], int flags);

/* Dup */
int dup(int oldfd);
int dup2(int oldfd, int newfd);
int dup3(int oldfd, int newfd, int flags);

/* User/group IDs */
uid_t getuid(void);
gid_t getgid(void);
uid_t geteuid(void);
gid_t getegid(void);
int setuid(uid_t uid);
int setgid(gid_t gid);
int seteuid(uid_t euid);
int setegid(gid_t egid);
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid);
int getgroups(int size, gid_t list[]);
int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid);
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

/* Process */
pid_t getppid(void);
pid_t getpgid(pid_t pid);
int setpgid(pid_t pid, pid_t pgid);
pid_t tcgetpgrp(int fd);
int tcsetpgrp(int fd, pid_t pgrp);

/* Terminal */
/* cfsetspeed declared in termios.h stub */
/* Network */struct sockaddr;
int getsockname(int sockfd, struct sockaddr *addr, unsigned int *addrlen);int getpeername(int sockfd, struct sockaddr *addr, unsigned int *addrlen);int sethostname(const char *name, size_t len);int gethostname(char *name, size_t len);/* Exec */int execle(const char *path, const char *arg, ...);
/* BSD socket functions (wasi-libc guards behind __wasilibc_unmodified_upstream) */int socket(int domain, int type, int protocol);int bind(int sockfd, const struct sockaddr *addr, unsigned int addrlen);int connect(int sockfd, const struct sockaddr *addr, unsigned int addrlen);int listen(int sockfd, int backlog);int accept(int sockfd, struct sockaddr *addr, unsigned int *addrlen);ssize_t send(int sockfd, const void *buf, size_t len, int flags);ssize_t recv(int sockfd, void *buf, size_t len, int flags);ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest, unsigned int addrlen);ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src, unsigned int *addrlen);int setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen);int getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen);int shutdown(int sockfd, int how);

/* Shadow passwords */
struct spwd;
int getspnam_r(const char *name, struct spwd *spbuf, char *buf, size_t buflen, struct spwd **spbufp);

/* Miscellaneous */
int nice(int inc);
unsigned int alarm(unsigned int seconds);
int pause(void);
char *ttyname(int fd);
int ttyname_r(int fd, char *buf, size_t buflen);
int isatty(int fd);
long sysconf(int name);
int link(const char *oldpath, const char *newpath);
int symlink(const char *target, const char *linkpath);
ssize_t readlink(const char *path, char *buf, size_t bufsiz);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
int access(const char *path, int mode);
long pathconf(const char *path, int name);
long fpathconf(int fd, int name);
int chdir(const char *path);
int fchdir(int fd);
char *getcwd(char *buf, size_t size);

/* Sysconf names */
#ifndef _SC_CLK_TCK
#define _SC_CLK_TCK          2
#define _SC_OPEN_MAX         4
#define _SC_PAGESIZE         30
#define _SC_PAGE_SIZE        _SC_PAGESIZE
#define _SC_NPROCESSORS_CONF 83
#define _SC_NPROCESSORS_ONLN 84
#define _SC_PHYS_PAGES       85
#endif

/* Wait status macros */
#ifndef WIFEXITED
#define WIFEXITED(s)   (((s) & 0x7f) == 0)
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WIFSIGNALED(s) (((signed char)(((s) & 0x7f) + 1) >> 1) > 0)
#define WTERMSIG(s)    ((s) & 0x7f)
#define WIFSTOPPED(s)  (((s) & 0xff) == 0x7f)
#define WSTOPSIG(s)    WEXITSTATUS(s)
#endif


/* PTY */
int grantpt(int fd);
int unlockpt(int fd);
int ptsname_r(int fd, char *buf, size_t buflen);

/* Timezone */
void tzset(void);

/* Serial ioctls */
#ifndef TIOCSSERIAL
#define TIOCSSERIAL 0x541F
#define TIOCGSERIAL 0x541E
#define TIOCSERCONFIG 0x5453
#endif

/* Packet socket */
#ifndef SOL_PACKET
#define SOL_PACKET 263
#endif
#ifndef TP_STATUS_CSUMNOTREADY
#define TP_STATUS_CSUMNOTREADY (1 << 3)
#endif

/* Message headers for sendmsg/recvmsg */
struct cmsghdr {
    unsigned int cmsg_len;
    int cmsg_level;
    int cmsg_type;
};

/* struct msghdr provided by wasi-libc __struct_msghdr.h */

#ifndef CMSG_ALIGN
#define CMSG_ALIGN(len) (((len) + sizeof(long) - 1) & ~(sizeof(long) - 1))
#define CMSG_LEN(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + (len))
#define CMSG_DATA(cmsg) ((unsigned char *)((struct cmsghdr *)(cmsg) + 1))
#define CMSG_FIRSTHDR(mhdr) \
    ((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? \
     (struct cmsghdr *)(mhdr)->msg_control : (struct cmsghdr *)0)
#define CMSG_NXTHDR(mhdr, cmsg) \
    ((cmsg)->cmsg_len < sizeof(struct cmsghdr) ? (struct cmsghdr *)0 : \
     ((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len) + sizeof(struct cmsghdr) > \
      (unsigned char *)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
     (struct cmsghdr *)0 : \
     (struct cmsghdr *)((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len)))
#endif

/* sendmsg/recvmsg */
struct iovec;
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);


/* O_NDELAY alias for O_NONBLOCK */
#include <fcntl.h>
/* Override wasi-libc truncated sockaddr_un (no sun_path) */
#define __wasilibc___struct_sockaddr_un_h
#include <__typedef_sa_family_t.h>
struct sockaddr_un {
    sa_family_t sun_family;
    char sun_path[108];
};
#ifndef O_NDELAY
#define O_NDELAY O_NONBLOCK
#endif

/* File locking: wasi-libc does NOT provide any of these */
#ifndef F_RDLCK
#define F_RDLCK  0
#define F_WRLCK  1
#define F_UNLCK  2
#endif
#ifndef F_DUPFD
#define F_DUPFD  0
#define F_DUPFD_CLOEXEC 1030
#endif
#ifndef F_GETLK
#define F_GETLK  5
#define F_SETLK  6
#define F_SETLKW 7
#endif

/* MSG_DONTWAIT */
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0x40
#endif

/* CMSG_SPACE */
#ifndef CMSG_SPACE
#define CMSG_SPACE(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))
#endif


/* Process groups */
pid_t getpgrp(void);
int setpgrp(void);

/* Signal set operations */
int sigisemptyset(const sigset_t *set);

/* Temp files */
int mkstemp(char *tmpl);
int mkostemp(char *tmpl, int flags);
int mkstemps(char *tmpl, int suffixlen);
char *mkdtemp(char *tmpl);

/* Time */
struct timeval;
int settimeofday(const struct timeval *tv, const void *tz);
int gettimeofday(struct timeval *tv, void *tz);


/* Name info flags */
#ifndef NI_NAMEREQD
#define NI_NUMERICHOST 1
#define NI_NUMERICSERV 2
#define NI_NOFQDN      4
#define NI_NAMEREQD    8
#define NI_DGRAM       16
#endif


/* Socket options (ensure availability regardless of include order) */
#ifndef SO_REUSEADDR
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
#endif

/* Block device ioctl */
#ifndef BLKFLSBUF
#define BLKFLSBUF    0x1261
#define BLKGETSIZE   0x1260
#define BLKGETSIZE64 0x80081272
#endif
#ifndef _IO
#define _IO(type,nr)    ((type)<<8|(nr))
#define _IOR(type,nr,size)  _IO(type,nr)
#define _IOW(type,nr,size)  _IO(type,nr)
#define _IOWR(type,nr,size) _IO(type,nr)
#endif


/* Socket options (ensure availability regardless of include order) */
#ifndef SO_REUSEADDR
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
#endif

/* Block device ioctl */
#ifndef BLKFLSBUF
#define BLKFLSBUF    0x1261
#define BLKGETSIZE   0x1260
#define BLKGETSIZE64 0x80081272
#endif
#ifndef _IO
#define _IO(type,nr)    ((type)<<8|(nr))
#define _IOR(type,nr,size)  _IO(type,nr)
#define _IOW(type,nr,size)  _IO(type,nr)
#define _IOWR(type,nr,size) _IO(type,nr)
#endif

#endif
#endif /* \!__ASSEMBLER__ */
