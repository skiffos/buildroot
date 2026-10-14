#ifndef _LINUX_FILTER_H
#define _LINUX_FILTER_H
#include <linux/types.h>
struct sock_filter { __u16 code; __u8 jt; __u8 jf; __u32 k; };
struct sock_fprog { unsigned short len; struct sock_filter *filter; };
#define BPF_LD   0x00
#define BPF_JMP  0x05
#define BPF_RET  0x06
#define BPF_ABS  0x20
#define BPF_K    0x00
#define BPF_JEQ  0x10
#define BPF_W    0x00
#define BPF_H    0x08
#define BPF_B    0x10
#define SO_ATTACH_FILTER 26
#endif
