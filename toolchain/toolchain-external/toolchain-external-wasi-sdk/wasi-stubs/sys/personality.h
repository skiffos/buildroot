#ifndef _SYS_PERSONALITY_H
#define _SYS_PERSONALITY_H
#define PER_LINUX   0x0000
#define PER_LINUX32 0x0008
#define PER_LINUX_32BIT 0x0800000
#define ADDR_NO_RANDOMIZE 0x0040000
int personality(unsigned long persona);
#endif
