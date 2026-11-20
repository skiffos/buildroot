// Replacement temporary file functions, which wasi-libc lacks, from musl
// (MIT license). Each replaces the template's trailing XXXXXX with a random
// name and creates the file or directory exclusively.

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// randname writes six random letters to template. The counter separates
// names drawn within one clock tick.
static char *randname(char *template)
{
	static unsigned long seq;
	struct timespec ts;
	unsigned long r;
	int i;

	clock_gettime(CLOCK_REALTIME, &ts);
	r = ts.tv_sec + ts.tv_nsec + ++seq * 65537UL;
	for (i = 0; i < 6; i++, r >>= 5)
		template[i] = 'A' + (r & 15) + (r & 16) * 2;
	return template;
}

char *mktemp(char *template)
{
	size_t l = strlen(template);
	int retries = 100;
	struct stat st;

	if (l < 6 || memcmp(template + l - 6, "XXXXXX", 6)) {
		errno = EINVAL;
		*template = 0;
		return template;
	}
	do {
		randname(template + l - 6);
		if (stat(template, &st)) {
			if (errno != ENOENT) *template = 0;
			return template;
		}
	} while (--retries);
	*template = 0;
	errno = EEXIST;
	return template;
}

int mkostemps(char *template, int len, int flags)
{
	size_t l = strlen(template);
	int fd, retries = 100;

	if (l < 6 || len < 0 || (size_t)len > l - 6 ||
	    memcmp(template + l - len - 6, "XXXXXX", 6)) {
		errno = EINVAL;
		return -1;
	}
	flags -= flags & O_ACCMODE;
	do {
		randname(template + l - len - 6);
		fd = open(template, flags | O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0) return fd;
	} while (--retries && errno == EEXIST);
	memcpy(template + l - len - 6, "XXXXXX", 6);
	return -1;
}

int mkstemp(char *template)
{
	return mkostemps(template, 0, 0);
}

int mkostemp(char *template, int flags)
{
	return mkostemps(template, 0, flags);
}

int mkstemps(char *template, int len)
{
	return mkostemps(template, len, 0);
}

char *mkdtemp(char *template)
{
	size_t l = strlen(template);
	int retries = 100;

	if (l < 6 || memcmp(template + l - 6, "XXXXXX", 6)) {
		errno = EINVAL;
		return 0;
	}
	do {
		randname(template + l - 6);
		if (!mkdir(template, 0700)) return template;
	} while (--retries && errno == EEXIST);
	memcpy(template + l - 6, "XXXXXX", 6);
	return 0;
}
