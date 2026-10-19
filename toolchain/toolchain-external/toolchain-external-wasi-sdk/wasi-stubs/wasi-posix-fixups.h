#ifndef __ASSEMBLER__
/* POSIX compatibility layer for wasi-libc.
 *
 * Included at the end of the libc headers it extends, so it follows a
 * package's config.h and feature macros like any libc header. Provides
 * constants, structs, and function declarations that wasi-libc
 * deliberately omits (guarded behind __wasilibc_unmodified_upstream).
 *
 * The functions are host imports: the wasivm kernel implements each one
 * named in wasivm.imports.
 */
#ifndef _WASI_POSIX_FIXUPS_H
#define _WASI_POSIX_FIXUPS_H

#include <sys/types.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#ifndef PF_UNIX
#define PF_UNIX AF_UNIX
#endif
#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#define PF_LOCAL AF_UNIX
#endif

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
#ifndef SO_ACCEPTCONN
#define SO_ACCEPTCONN   30
#define SO_DOMAIN       39
#endif

#ifndef SOL_PACKET
#define SOL_PACKET 263
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0x40
#endif

/* The kernel takes MSG_NOSIGNAL to fail a write to a closed peer with EPIPE
 * and no SIGPIPE. */
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0x4000
#endif

/* WASI has no out-of-band data, so poll never reports POLLPRI. */
#ifndef POLLPRI
#define POLLPRI 0x0200
#endif

#ifndef MSG_CTRUNC
#define MSG_CTRUNC 0x8
#endif

#ifndef MSG_CMSG_CLOEXEC
#define MSG_CMSG_CLOEXEC 0x40000000
#endif

/* The kernel passes descriptors in SCM_RIGHTS messages. */
#ifndef SCM_RIGHTS
#define SCM_RIGHTS 0x01
#define SCM_CREDENTIALS 0x02
#endif

/* A Unix socket's peer credentials, read into sys/socket.h's struct ucred. */
#ifndef SO_PEERCRED
#define SO_PEERCRED 17
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

/* Define sigset_t before signal.h, which a package's replacement signal.h
 * may wrap and declare functions of sigset_t before the libc header runs. */
#include <__typedef_sigset_t.h>
#include <signal.h>

#ifndef SA_RESTART
#define SA_RESTART   0x10000000
#define SA_NODEFER   0x40000000
#define SA_RESETHAND 0x80000000
#define SA_NOCLDSTOP 1
#define SA_NOCLDWAIT 2
#define SA_ONSTACK   0x08000000
#endif

/* The real-time signal range of musl. The kernel sends only the standard
 * signals, so a program sees these only as the bounds of its tables. */
#ifndef SIGRTMIN
#define SIGRTMIN 35
#define SIGRTMAX 64
#endif

#ifndef SIG_BLOCK
#define SIG_BLOCK   0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#endif

#ifndef _WASI_SIGINFO_DEFINED
#define _WASI_SIGINFO_DEFINED
/* Linux's siginfo_t, 128 bytes holding the signal, its cause and the
 * fields of that cause. */
typedef struct {
    int si_signo;
    int si_errno;
    int si_code;
    union {
        char __si_pad[128 - 3 * sizeof(int)];
        struct {
            pid_t si_pid;
            uid_t si_uid;
            int si_status;
        };
        void *si_addr;
    };
} siginfo_t;
#endif

#ifndef SA_SIGINFO
#define SA_SIGINFO 4
#endif

#ifndef _WASI_SIGACTION_DEFINED
#define _WASI_SIGACTION_DEFINED
/* The wasivm kernel reads the handler, the flags and then the mask. It calls
 * the handler with the signal number alone, so it refuses SA_SIGINFO and
 * never calls sa_sigaction. */
struct sigaction {
    union {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t *, void *);
    } __sa_handler;
    unsigned long sa_flags;
    sigset_t sa_mask;
};
#define sa_handler   __sa_handler.sa_handler
#define sa_sigaction __sa_handler.sa_sigaction
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
int pthread_sigmask(int, const sigset_t *, sigset_t *);
int sigtimedwait(const sigset_t *, siginfo_t *, const struct timespec *);
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

/* The WasiVM kernel reads O_NOCTTY and O_CLOEXEC from bits of path_open's
 * fdflags that WASI leaves unused, where wasi-libc's open passes the low open
 * flags. wasi-libc defines O_CLOEXEC as zero. */
#include <__header_fcntl.h>
#undef O_NOCTTY
#define O_NOCTTY 0x100
#undef O_CLOEXEC
#define O_CLOEXEC 0x200

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

/* File seals, which the kernel keeps for a memfd made with
 * MFD_ALLOW_SEALING. */
#ifndef F_ADD_SEALS
#define F_ADD_SEALS         1033
#define F_GET_SEALS         1034
#define F_SEAL_SEAL         0x0001
#define F_SEAL_SHRINK       0x0002
#define F_SEAL_GROW         0x0004
#define F_SEAL_WRITE        0x0008
#define F_SEAL_FUTURE_WRITE 0x0010
#define F_SEAL_EXEC         0x0020
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
#ifndef TIOCGPTN
#define TIOCGSID   0x5429
#define TIOCGPTN   0x80045430
#define TIOCSPTLCK 0x40045431
#endif

/* The kernel serves FIONREAD and FIONBIO in their Linux values, which replace
 * the values of wasi-libc's own ioctl. Its header comes first, so a later
 * include cannot restore them. */
#include <__header_sys_ioctl.h>
#undef FIONREAD
#undef FIONBIO
#define FIONREAD 0x541B
#define FIONBIO  0x5421
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
int posix_openpt(int);
char *ptsname(int);
int grantpt(int);
int unlockpt(int);
int ptsname_r(int, char *, size_t);

/* Host names, which unistd.h declares. */
int sethostname(const char *, size_t);
int gethostname(char *, size_t);

/* ================================================================
 * Resource limits and priority
 * ================================================================ */

#ifndef RLIMIT_CORE
/* 64 bits, as in musl: the kernel reads and writes two 64-bit limits. */
typedef unsigned long long rlim_t;
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
#ifndef RLIM_SAVED_CUR
#define RLIM_SAVED_CUR RLIM_INFINITY
#define RLIM_SAVED_MAX RLIM_INFINITY
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

/* The Linux clocks wasi-libc does not name, as clock objects like its own. */
#ifndef CLOCK_BOOTTIME
extern const struct __clockid _CLOCK_PROCESS_CPUTIME_ID;
extern const struct __clockid _CLOCK_THREAD_CPUTIME_ID;
extern const struct __clockid _CLOCK_MONOTONIC_RAW;
extern const struct __clockid _CLOCK_REALTIME_COARSE;
extern const struct __clockid _CLOCK_MONOTONIC_COARSE;
extern const struct __clockid _CLOCK_BOOTTIME;
#define CLOCK_PROCESS_CPUTIME_ID (&_CLOCK_PROCESS_CPUTIME_ID)
#define CLOCK_THREAD_CPUTIME_ID  (&_CLOCK_THREAD_CPUTIME_ID)
#define CLOCK_MONOTONIC_RAW      (&_CLOCK_MONOTONIC_RAW)
#define CLOCK_REALTIME_COARSE    (&_CLOCK_REALTIME_COARSE)
#define CLOCK_MONOTONIC_COARSE   (&_CLOCK_MONOTONIC_COARSE)
#define CLOCK_BOOTTIME           (&_CLOCK_BOOTTIME)
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
/* Tagged as musl tags it, so pthread.h can name struct cpu_set_t in C++. */
typedef struct cpu_set_t {
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

/* wasi-libc defines these but hides their declarations. */
void qsort_r(void *, size_t, size_t,
             int (*)(const void *, const void *, void *), void *);
int getdomainname(char *, size_t);

/* wasi-libc claims _POSIX_THREAD_SAFE_FUNCTIONS; src/flockfile.c provides
 * the stream locks, which a single-threaded process does not need. */
struct _IO_FILE;
void flockfile(struct _IO_FILE *);
int ftrylockfile(struct _IO_FILE *);
void funlockfile(struct _IO_FILE *);

/* src/popen.c runs the command in a forked /bin/sh. */
struct _IO_FILE *popen(const char *, const char *);
int pclose(struct _IO_FILE *);

struct spwd;
int getspnam_r(const char *, struct spwd *, char *, size_t, struct spwd **);

#ifndef P_tmpdir
#define P_tmpdir "/tmp"
#endif
char *mktemp(char *);
int mkstemp(char *);
int mkostemp(char *, int);
int mkstemps(char *, int);
int mkostemps(char *, int, int);
char *mkdtemp(char *);

#ifndef TP_STATUS_CSUMNOTREADY
#define TP_STATUS_CSUMNOTREADY (1 << 3)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _WASI_POSIX_FIXUPS_H */

/* The socket calls and control messages, declared only with sys/socket.h
 * as in musl, so a program may give its own functions their names. */
#if defined(_SYS_SOCKET_H) && !defined(_WASI_POSIX_FIXUPS_SOCKET_H)
#define _WASI_POSIX_FIXUPS_SOCKET_H
#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================
 * Network
 * ================================================================ */

struct sockaddr;
struct iovec;
struct msghdr;

int socket(int, int, int);
int socketpair(int, int, int, int[2]);
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

#ifdef __cplusplus
}
#endif
#endif /* _WASI_POSIX_FIXUPS_SOCKET_H */
#endif /* \!__ASSEMBLER__ */
