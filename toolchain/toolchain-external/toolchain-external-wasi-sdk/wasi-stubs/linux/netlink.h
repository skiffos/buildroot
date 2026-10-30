#ifndef _LINUX_NETLINK_H
#define _LINUX_NETLINK_H

#define NETLINK_ROUTE   0
#define NETLINK_KOBJECT_UEVENT 15

struct sockaddr_nl {
    unsigned short nl_family;
    unsigned short nl_pad;
    unsigned int nl_pid;
    unsigned int nl_groups;
};

struct nlmsghdr {
    unsigned int nlmsg_len;
    unsigned short nlmsg_type;
    unsigned short nlmsg_flags;
    unsigned int nlmsg_seq;
    unsigned int nlmsg_pid;
};

#define NLMSG_ALIGNTO 4
#define NLMSG_ALIGN(len) (((len) + NLMSG_ALIGNTO - 1) & ~(NLMSG_ALIGNTO - 1))
#define NLMSG_HDRLEN ((int)NLMSG_ALIGN(sizeof(struct nlmsghdr)))
#define NLMSG_LENGTH(len) ((len) + NLMSG_HDRLEN)
#define NLMSG_DATA(nlh) ((void *)(((char *)nlh) + NLMSG_HDRLEN))
#define NLMSG_OK(nlh, len) ((len) >= (int)sizeof(struct nlmsghdr) && \
    (nlh)->nlmsg_len >= sizeof(struct nlmsghdr) && \
    (nlh)->nlmsg_len <= (len))
#define NLMSG_NEXT(nlh, len) ((len) -= NLMSG_ALIGN((nlh)->nlmsg_len), \
    (struct nlmsghdr *)(((char *)(nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len)))

#define NLMSG_DONE  3
#define NLMSG_ERROR 2

#define NLM_F_REQUEST  0x01
#define NLM_F_MULTI    0x02
#define NLM_F_ACK      0x04
#define NLM_F_ROOT     0x100
#define NLM_F_MATCH    0x200
#define NLM_F_ATOMIC   0x400
#define NLM_F_DUMP     (NLM_F_ROOT | NLM_F_MATCH)
#define NLM_F_REPLACE  0x100
#define NLM_F_EXCL     0x200
#define NLM_F_CREATE   0x400
#define NLM_F_APPEND   0x800

#endif
