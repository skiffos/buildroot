#ifndef _NET_ETHERNET_H
#define _NET_ETHERNET_H

#include <stdint.h>

#define ETH_ALEN 6
#define ETHERTYPE_IP   0x0800
#define ETHERTYPE_ARP  0x0806
#define ETHERTYPE_IPV6 0x86dd

struct ether_addr {
    uint8_t ether_addr_octet[ETH_ALEN];
};

struct ether_header {
    uint8_t ether_dhost[ETH_ALEN];
    uint8_t ether_shost[ETH_ALEN];
    uint16_t ether_type;
};

#endif
