#ifndef _LINUX_FD_H
#define _LINUX_FD_H
#define FDGETPRM 0x0204
struct floppy_struct {
    unsigned int size;
    unsigned int sect;
    unsigned int head;
    unsigned int track;
    unsigned int stretch;
    unsigned char gap;
    unsigned char rate;
    unsigned char spec1;
    unsigned char fmt_gap;
    const char *name;
};
#endif
