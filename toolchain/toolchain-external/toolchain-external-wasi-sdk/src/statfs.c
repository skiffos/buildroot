// statfs and fstatfs, which wasi-libc lacks, over its statvfs. statvfs names
// no filesystem type, so f_type is zero.

#include <string.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>

static void fixup(struct statfs *out, const struct statvfs *in)
{
	memset(out, 0, sizeof(*out));
	out->f_bsize = in->f_bsize;
	out->f_frsize = in->f_frsize;
	out->f_blocks = in->f_blocks;
	out->f_bfree = in->f_bfree;
	out->f_bavail = in->f_bavail;
	out->f_files = in->f_files;
	out->f_ffree = in->f_ffree;
	out->f_fsid.val[0] = in->f_fsid;
	out->f_namelen = in->f_namemax;
	out->f_flags = in->f_flag;
}

int statfs(const char *path, struct statfs *buf)
{
	struct statvfs st;
	if (statvfs(path, &st) < 0) return -1;
	fixup(buf, &st);
	return 0;
}

int fstatfs(int fd, struct statfs *buf)
{
	struct statvfs st;
	if (fstatvfs(fd, &st) < 0) return -1;
	fixup(buf, &st);
	return 0;
}
