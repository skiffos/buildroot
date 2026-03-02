#ifndef _SYS_INOTIFY_H
#define _SYS_INOTIFY_H
#include <stdint.h>
struct inotify_event { int wd; uint32_t mask; uint32_t cookie; uint32_t len; char name[]; };
#define IN_ACCESS        0x00000001
#define IN_MODIFY        0x00000002
#define IN_ATTRIB        0x00000004
#define IN_CLOSE_WRITE   0x00000008
#define IN_CLOSE_NOWRITE 0x00000010
#define IN_OPEN          0x00000020
#define IN_MOVED_FROM    0x00000040
#define IN_MOVED_TO      0x00000080
#define IN_CREATE        0x00000100
#define IN_DELETE         0x00000200
#define IN_DELETE_SELF    0x00000400
#define IN_MOVE_SELF     0x00000800
#define IN_CLOSE         (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)
#define IN_MOVE          (IN_MOVED_FROM | IN_MOVED_TO)
#define IN_ALL_EVENTS    0x00000fff
#define IN_NONBLOCK      04000
#define IN_CLOEXEC       02000000
int inotify_init(void);
int inotify_init1(int flags);
int inotify_add_watch(int fd, const char *path, uint32_t mask);
int inotify_rm_watch(int fd, int wd);
#endif
