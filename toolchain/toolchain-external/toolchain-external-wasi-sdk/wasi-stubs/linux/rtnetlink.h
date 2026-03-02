#ifndef _LINUX_RTNETLINK_H
#define _LINUX_RTNETLINK_H
#include <linux/netlink.h>
#include <linux/types.h>
#include <linux/if_addr.h>
#include <linux/if_link.h>

/* Netlink error message */
struct nlmsgerr {
    int error;
    struct nlmsghdr msg;
};

/* Generic netlink message */
struct rtgenmsg {
    unsigned char rtgen_family;
};

#define RTM_BASE     16
#define RTM_NEWLINK  16
#define RTM_DELLINK  17
#define RTM_GETLINK  18
#define RTM_SETLINK  19
#define RTM_NEWADDR  20
#define RTM_DELADDR  21
#define RTM_GETADDR  22
#define RTM_NEWROUTE 24
#define RTM_DELROUTE 25
#define RTM_GETROUTE 26
#define RTM_NEWNEIGH 28
#define RTM_DELNEIGH 29
#define RTM_GETNEIGH 30
#define RTM_NEWRULE  32
#define RTM_DELRULE  33
#define RTM_GETRULE  34

struct rtattr {
    unsigned short rta_len;
    unsigned short rta_type;
};

#define RTA_ALIGNTO 4
#define RTA_ALIGN(len) (((len)+RTA_ALIGNTO-1) & ~(RTA_ALIGNTO-1))
#define RTA_OK(rta,len) ((len) >= (int)sizeof(struct rtattr) && \
    (rta)->rta_len >= sizeof(struct rtattr) && (rta)->rta_len <= (len))
#define RTA_NEXT(rta,attrlen) ((attrlen) -= RTA_ALIGN((rta)->rta_len), \
    (struct rtattr*)(((char*)(rta)) + RTA_ALIGN((rta)->rta_len)))
#define RTA_LENGTH(len) (RTA_ALIGN(sizeof(struct rtattr)) + (len))
#define RTA_DATA(rta) ((void*)(((char*)(rta)) + RTA_LENGTH(0)))
#define RTA_PAYLOAD(rta) ((int)((rta)->rta_len) - RTA_LENGTH(0))

struct ifinfomsg {
    unsigned char ifi_family;
    unsigned char __ifi_pad;
    unsigned short ifi_type;
    int ifi_index;
    unsigned ifi_flags;
    unsigned ifi_change;
};

#define IFLA_RTA(r) ((struct rtattr *)(((char *)(r)) + \
    ((sizeof(struct ifinfomsg) + 3) & ~3)))
#define IFLA_PAYLOAD(n) ((int)((n)->nlmsg_len) - \
    NLMSG_LENGTH(sizeof(struct ifinfomsg)))

struct rtmsg {
    unsigned char rtm_family;
    unsigned char rtm_dst_len;
    unsigned char rtm_src_len;
    unsigned char rtm_tos;
    unsigned char rtm_table;
    unsigned char rtm_protocol;
    unsigned char rtm_scope;
    unsigned char rtm_type;
    unsigned rtm_flags;
};

#define RTM_RTA(r) ((struct rtattr *)(((char *)(r)) + \
    ((sizeof(struct rtmsg) + 3) & ~3)))

/* Route attributes */
#define RTA_UNSPEC   0
#define RTA_DST      1
#define RTA_SRC      2
#define RTA_IIF      3
#define RTA_OIF      4
#define RTA_GATEWAY  5
#define RTA_PRIORITY 6
#define RTA_PREFSRC  7
#define RTA_METRICS  8
#define RTA_MULTIPATH 9
#define RTA_FLOW     11
#define RTA_CACHEINFO 12
#define RTA_TABLE    15
#define __RTA_MAX    16
#define RTA_MAX (__RTA_MAX - 1)

/* Route types */
#define RTN_UNSPEC      0
#define RTN_UNICAST     1
#define RTN_LOCAL       2
#define RTN_BROADCAST   3
#define RTN_ANYCAST     4
#define RTN_MULTICAST   5
#define RTN_BLACKHOLE   6
#define RTN_UNREACHABLE 7
#define RTN_PROHIBIT    8
#define RTN_THROW       9
#define RTN_NAT         10
#define RTN_XRESOLVE    11

/* Route flags */
#define RTM_F_NOTIFY  0x100
#define RTM_F_CLONED  0x200
#define RTM_F_EQUALIZE 0x400

/* Route scope */
#define RT_SCOPE_UNIVERSE 0
#define RT_SCOPE_SITE     200
#define RT_SCOPE_LINK     253
#define RT_SCOPE_HOST     254
#define RT_SCOPE_NOWHERE  255

/* Route table */
#define RT_TABLE_UNSPEC  0
#define RT_TABLE_DEFAULT 253
#define RT_TABLE_MAIN    254
#define RT_TABLE_LOCAL   255

/* Route protocol */
#define RTPROT_UNSPEC   0
#define RTPROT_REDIRECT 1
#define RTPROT_KERNEL   2
#define RTPROT_BOOT     3
#define RTPROT_STATIC   4


/* Route nexthop flags */
#define RTNH_F_DEAD      1
#define RTNH_F_PERVASIVE 2
#define RTNH_F_ONLINK    4

struct rtnexthop {
    unsigned short rtnh_len;
    unsigned char rtnh_flags;
    unsigned char rtnh_hops;
    int rtnh_ifindex;
};

#define RTNH_ALIGNTO 4
#define RTNH_ALIGN(len) (((len)+RTNH_ALIGNTO-1) & ~(RTNH_ALIGNTO-1))
#define RTNH_DATA(rtnh) ((struct rtattr *)(((char *)(rtnh)) + RTNH_ALIGN(sizeof(struct rtnexthop))))
#define RTNH_NEXT(rtnh) ((struct rtnexthop *)(((char *)(rtnh)) + RTNH_ALIGN((rtnh)->rtnh_len)))

/* Route cache info */
struct rta_cacheinfo {
    unsigned int rta_clntref;
    unsigned int rta_lastuse;
    int rta_expires;
    unsigned int rta_error;
    unsigned int rta_used;
    unsigned int rta_id;
    unsigned int rta_ts;
    unsigned int rta_tsage;
};

/* Route metrics attributes */
#define RTAX_UNSPEC   0
#define RTAX_LOCK     1
#define RTAX_MTU      2
#define RTAX_WINDOW   3
#define RTAX_RTT      4
#define RTAX_RTTVAR   5
#define RTAX_SSTHRESH 6
#define RTAX_CWND     7
#define RTAX_ADVMSS   8
#define RTAX_REORDERING 9
#define RTAX_HOPLIMIT 10
#define RTAX_INITCWND 11
#define RTAX_FEATURES 12

#endif
