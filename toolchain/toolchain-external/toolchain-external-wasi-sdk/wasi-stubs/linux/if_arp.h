#ifndef _LINUX_IF_ARP_H
#define _LINUX_IF_ARP_H
#include <net/if_arp.h>

#ifndef ARPHRD_IPGRE
#define ARPHRD_IPGRE    778
#define ARPHRD_IP6GRE   823
#define ARPHRD_SIT      776
#define ARPHRD_TUNNEL   768
#define ARPHRD_TUNNEL6  769
#define ARPHRD_NONE     0xFFFE
#define ARPHRD_VOID     0xFFFF
#endif

/* struct arphdr provided by net/if_arp.h */

#endif
