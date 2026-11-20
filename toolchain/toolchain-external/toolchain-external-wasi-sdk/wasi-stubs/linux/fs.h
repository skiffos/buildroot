#ifndef _LINUX_FS_H
#define _LINUX_FS_H
#define BLKROSET   _IO(0x12,  93)
#define BLKROGET   _IO(0x12,  94)
#define BLKRRPART  _IO(0x12,  95)
#define BLKGETSIZE _IO(0x12,  96)
#define BLKFLSBUF  _IO(0x12,  97)
#define BLKSSZGET  _IO(0x12, 104)
#define BLKGETSIZE64 _IOR(0x12, 114, size_t)
#ifndef _IO
#define _IO(type, nr)       (((type) << 8) | (nr))
#define _IOR(type, nr, sz)  (((type) << 8) | (nr))
#define _IOW(type, nr, sz)  (((type) << 8) | (nr))
#define _IOWR(type, nr, sz) (((type) << 8) | (nr))
#endif
#define MS_RDONLY 1
#define MS_NOSUID 2
#define MS_NODEV  4
#define RENAME_NOREPLACE (1 << 0)
#define RENAME_EXCHANGE  (1 << 1)
#endif
