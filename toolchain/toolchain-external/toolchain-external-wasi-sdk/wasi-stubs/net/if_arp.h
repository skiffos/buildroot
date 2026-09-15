#ifndef _NET_IF_ARP_H
#define _NET_IF_ARP_H
#include <stdint.h>
#define ARPHRD_ETHER    1
#define ARPHRD_LOOPBACK 772
#define ARPHRD_PPP      512
#define ARPHRD_SIT      776
#define ARPHRD_TUNNEL   768
#define ARPHRD_VOID     0xFFFF
#define ARPHRD_CSLIP      257
#define ARPHRD_SLIP       256
#define ARPHRD_INFINIBAND 32
#define ARPHRD_IEEE802    6
#define ARPHRD_IEEE80211  801
#define ARPHRD_DLCI       15
#define ARPHRD_SLIP6    257
#define ARPHRD_CSLIP6     258
#define ARPHRD_ADAPT      264
#define ARPHRD_ROSE       270
#define ARPHRD_X25        271
#define ARPHRD_FCPP       784
#define ARPHRD_FCAL       785
#define ARPHRD_FCPL       786
#define ARPHRD_IRDA       783
struct arphdr { uint16_t ar_hrd; uint16_t ar_pro; uint8_t ar_hln; uint8_t ar_pln; uint16_t ar_op; };
#define ARPOP_REQUEST 1
#define ARPOP_REPLY   2

#ifndef ARPHRD_IPGRE
#define ARPHRD_IPGRE    778
#define ARPHRD_IP6GRE   823
#define ARPHRD_SIT      776
#define ARPHRD_TUNNEL   768
#define ARPHRD_TUNNEL6  769
#define ARPHRD_NONE     0xFFFE
#define ARPHRD_VOID     0xFFFF
#endif

#endif
