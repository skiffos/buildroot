#ifndef _LINUX_HDREG_H
#define _LINUX_HDREG_H
#define HDIO_GETGEO 0x0301
struct hd_geometry {
    unsigned char heads;
    unsigned char sectors;
    unsigned short cylinders;
    unsigned long start;
};
#endif
