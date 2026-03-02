// Replacement fstat that adds default permissions and st_blocks.
// Same rationale as fstatat.c but for file descriptor stat.

#include <sys/stat.h>
#include <errno.h>
#include <wasi/api.h>

int fstat(int fildes, struct stat *buf) {
    __wasi_filestat_t st;
    __wasi_errno_t error = __wasi_fd_filestat_get(fildes, &st);
    if (error != 0) {
        errno = error;
        return -1;
    }
    *buf = (struct stat){
        .st_dev = st.dev,
        .st_ino = st.ino,
        .st_nlink = st.nlink,
        .st_size = st.size,
        .st_atim = {.tv_sec = st.atim / 1000000000ULL,
                    .tv_nsec = st.atim % 1000000000ULL},
        .st_mtim = {.tv_sec = st.mtim / 1000000000ULL,
                    .tv_nsec = st.mtim % 1000000000ULL},
        .st_ctim = {.tv_sec = st.ctim / 1000000000ULL,
                    .tv_nsec = st.ctim % 1000000000ULL},
        .st_blksize = 4096,
    };
    switch (st.filetype) {
    case __WASI_FILETYPE_BLOCK_DEVICE:
        break;
    case __WASI_FILETYPE_CHARACTER_DEVICE:
        buf->st_mode |= S_IFCHR;
        break;
    case __WASI_FILETYPE_DIRECTORY:
        buf->st_mode |= S_IFDIR;
        break;
    case __WASI_FILETYPE_REGULAR_FILE:
        buf->st_mode |= S_IFREG;
        break;
    case __WASI_FILETYPE_SOCKET_DGRAM:
    case __WASI_FILETYPE_SOCKET_STREAM:
        buf->st_mode |= S_IFSOCK;
        break;
    case __WASI_FILETYPE_SYMBOLIC_LINK:
        buf->st_mode |= S_IFLNK;
        break;
    }
    buf->st_mode |= 0755;
    buf->st_blocks = (buf->st_size + 511) / 512;
    return 0;
}
