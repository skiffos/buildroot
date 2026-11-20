#ifndef _SYS_SENDFILE_H
#define _SYS_SENDFILE_H

#include <sys/types.h>

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);

#endif
