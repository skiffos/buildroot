#ifndef _LINUX_IF_ADDR_H
#define _LINUX_IF_ADDR_H
#include <linux/types.h>

struct rtattr;

struct ifaddrmsg {
    __u8 ifa_family;
    __u8 ifa_prefixlen;
    __u8 ifa_flags;
    __u8 ifa_scope;
    __u32 ifa_index;
};

#define IFA_UNSPEC    0
#define IFA_ADDRESS   1
#define IFA_LOCAL     2
#define IFA_LABEL     3
#define IFA_BROADCAST 4
#define IFA_ANYCAST   5
#define IFA_CACHEINFO 6
#define IFA_MULTICAST 7
#define IFA_FLAGS     8
#define __IFA_MAX     9
#define IFA_MAX (__IFA_MAX - 1)

#define IFA_RTA(r) ((struct rtattr *)(((char *)(r)) + \
    ((sizeof(struct ifaddrmsg) + 3) & ~3)))

#define IFA_PAYLOAD(n) ((int)((n)->nlmsg_len) - NLMSG_LENGTH(sizeof(struct ifaddrmsg)))

#define IFA_F_SECONDARY   0x01
#define IFA_F_NODAD       0x02
#define IFA_F_OPTIMISTIC  0x04
#define IFA_F_DADFAILED   0x08
#define IFA_F_HOMEADDRESS 0x10
#define IFA_F_DEPRECATED  0x20
#define IFA_F_TENTATIVE   0x40
#define IFA_F_PERMANENT   0x80

struct ifa_cacheinfo {
    __u32 ifa_prefered;
    __u32 ifa_valid;
    __u32 cstamp;
    __u32 tstamp;
};

#endif
