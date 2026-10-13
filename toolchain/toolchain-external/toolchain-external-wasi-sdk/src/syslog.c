// syslog, which wasi-libc lacks. The kernel has no Unix sockets, so no log
// daemon is reachable: as musl does when /dev/log is missing, a message goes
// to the console with LOG_CONS and to stderr with LOG_PERROR.

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

static char log_ident[32];
static int log_opt;
static int log_mask = 0xff;

void openlog(const char *ident, int opt, int facility)
{
	if (ident) {
		strncpy(log_ident, ident, sizeof(log_ident) - 1);
		log_ident[sizeof(log_ident) - 1] = 0;
	} else {
		log_ident[0] = 0;
	}
	log_opt = opt;
}

void closelog(void)
{
}

int setlogmask(int mask)
{
	int old = log_mask;
	if (mask) log_mask = mask;
	return old;
}

void vsyslog(int priority, const char *message, va_list ap)
{
	char buf[1024];
	int n, fd;

	if (!(log_mask & (1 << (priority & 7)))) return;
	if (!(log_opt & (LOG_CONS | LOG_PERROR))) return;

	n = snprintf(buf, sizeof(buf), "%s", log_ident);
	if (log_opt & LOG_PID) n += snprintf(buf + n, sizeof(buf) - n, "[%d]", getpid());
	if (n) n += snprintf(buf + n, sizeof(buf) - n, ": ");
	n += vsnprintf(buf + n, sizeof(buf) - n, message, ap);
	if (n > (int)sizeof(buf) - 2) n = sizeof(buf) - 2;
	if (n == 0 || buf[n - 1] != '\n') buf[n++] = '\n';

	if (log_opt & LOG_PERROR) write(2, buf, n);
	if ((log_opt & LOG_CONS) && (fd = open("/dev/console", O_WRONLY | O_NOCTTY)) >= 0) {
		write(fd, buf, n);
		close(fd);
	}
}

void syslog(int priority, const char *message, ...)
{
	va_list ap;
	va_start(ap, message);
	vsyslog(priority, message, ap);
	va_end(ap);
}
