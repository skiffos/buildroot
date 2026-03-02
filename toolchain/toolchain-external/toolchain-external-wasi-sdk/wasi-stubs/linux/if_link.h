#ifndef _LINUX_IF_LINK_H
#define _LINUX_IF_LINK_H
#include <linux/types.h>

#ifndef IFLA_UNSPEC
#define IFLA_UNSPEC     0
#define IFLA_ADDRESS    1
#define IFLA_BROADCAST  2
#define IFLA_IFNAME     3
#define IFLA_MTU        4
#define IFLA_LINK       5
#define IFLA_QDISC      6
#define IFLA_STATS      7
#define IFLA_COST       8
#define IFLA_PRIORITY   9
#define IFLA_MASTER     10
#define IFLA_WIRELESS   11
#define IFLA_PROTINFO   12
#define IFLA_TXQLEN     13
#define IFLA_MAP        14
#define IFLA_WEIGHT     15
#define IFLA_OPERSTATE  16
#define IFLA_LINKMODE   17
#define IFLA_LINKINFO   18
#define IFLA_NET_NS_PID 19
#define IFLA_IFALIAS    20
#define __IFLA_MAX      21
#define IFLA_MAX (__IFLA_MAX - 1)
#endif

struct rtnl_link_stats {
    __u32 rx_packets;
    __u32 tx_packets;
    __u32 rx_bytes;
    __u32 tx_bytes;
    __u32 rx_errors;
    __u32 tx_errors;
    __u32 rx_dropped;
    __u32 tx_dropped;
    __u32 multicast;
    __u32 collisions;
    __u32 rx_length_errors;
    __u32 rx_over_errors;
    __u32 rx_crc_errors;
    __u32 rx_frame_errors;
    __u32 rx_fifo_errors;
    __u32 rx_missed_errors;
    __u32 tx_aborted_errors;
    __u32 tx_carrier_errors;
    __u32 tx_fifo_errors;
    __u32 tx_heartbeat_errors;
    __u32 tx_window_errors;
    __u32 rx_compressed;
    __u32 tx_compressed;
};

struct rtnl_link_stats64 {
    __u64 rx_packets;
    __u64 tx_packets;
    __u64 rx_bytes;
    __u64 tx_bytes;
    __u64 rx_errors;
    __u64 tx_errors;
    __u64 rx_dropped;
    __u64 tx_dropped;
    __u64 multicast;
    __u64 collisions;
    __u64 rx_length_errors;
    __u64 rx_over_errors;
    __u64 rx_crc_errors;
    __u64 rx_frame_errors;
    __u64 rx_fifo_errors;
    __u64 rx_missed_errors;
    __u64 tx_aborted_errors;
    __u64 tx_carrier_errors;
    __u64 tx_fifo_errors;
    __u64 tx_heartbeat_errors;
    __u64 tx_window_errors;
    __u64 rx_compressed;
    __u64 tx_compressed;
};

#endif

/* Appended: link info attributes */
#ifndef IFLA_INFO_KIND
#define IFLA_INFO_UNSPEC 0
#define IFLA_INFO_KIND   1
#define IFLA_INFO_DATA   2
#define IFLA_INFO_XSTATS 3

#endif
