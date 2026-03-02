#ifndef _SYS_PRCTL_H
#define _SYS_PRCTL_H

#define PR_SET_NAME    15
#define PR_GET_NAME    16
#define PR_SET_DUMPABLE 4
#define PR_GET_DUMPABLE 3

int prctl(int option, ...);

#endif
