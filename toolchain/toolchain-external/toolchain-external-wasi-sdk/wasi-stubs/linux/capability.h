#ifndef _LINUX_CAPABILITY_H
#define _LINUX_CAPABILITY_H
#include <stdint.h>
#define _LINUX_CAPABILITY_VERSION_1 0x19980330
#define _LINUX_CAPABILITY_U32S_1 1
#define _LINUX_CAPABILITY_VERSION_2 0x20071026
#define _LINUX_CAPABILITY_U32S_2 2
#define _LINUX_CAPABILITY_VERSION_3 0x20080522
#define _LINUX_CAPABILITY_U32S_3 2
struct __user_cap_header_struct { uint32_t version; int pid; };
typedef struct __user_cap_header_struct *cap_user_header_t;
struct __user_cap_data_struct { uint32_t effective; uint32_t permitted; uint32_t inheritable; };
typedef struct __user_cap_data_struct *cap_user_data_t;
int capget(cap_user_header_t hdrp, cap_user_data_t datap);
int capset(cap_user_header_t hdrp, const cap_user_data_t datap);
#define CAP_CHOWN            0
#define CAP_DAC_OVERRIDE     1
#define CAP_DAC_READ_SEARCH  2
#define CAP_FOWNER           3
#define CAP_FSETID           4
#define CAP_KILL             5
#define CAP_SETGID           6
#define CAP_SETUID           7
#define CAP_SETPCAP          8
#define CAP_NET_BIND_SERVICE 10
#define CAP_NET_RAW          13
#define CAP_SYS_CHROOT       18
#define CAP_SYS_ADMIN        21
#define CAP_SYS_RESOURCE     24
#define CAP_LAST_CAP         40
#define cap_valid(x) ((x) >= 0 && (x) <= CAP_LAST_CAP)
/* cap_name_count placeholder for busybox */

#define CAP_TO_INDEX(x) ((x) >> 5)
#define CAP_TO_MASK(x)  (1 << ((x) & 31))

#endif
