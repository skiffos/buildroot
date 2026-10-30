// ptsname, openpty, login_tty and forkpty for the WasiVM kernel, after musl.
// The kernel names a pty by the index TIOCGPTN reads from its master.

#include <errno.h>
#include <fcntl.h>
#include <pty.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <utmp.h>

int ptsname_r(int fd, char *buf, size_t len)
{
	int n;
	if (ioctl(fd, TIOCGPTN, &n))
		return errno;
	if (!buf || snprintf(buf, len, "/dev/pts/%d", n) >= (int)len)
		return ERANGE;
	return 0;
}

char *ptsname(int fd)
{
	static char buf[9 + sizeof(int) * 3 + 1];
	int err = ptsname_r(fd, buf, sizeof buf);
	if (err) {
		errno = err;
		return 0;
	}
	return buf;
}

int openpty(int *pm, int *ps, char *name, const struct termios *tio,
	const struct winsize *ws)
{
	char buf[20];
	int n = 0;
	int m = posix_openpt(O_RDWR | O_NOCTTY);
	if (m < 0)
		return -1;
	if (ioctl(m, TIOCSPTLCK, &n) || ioctl(m, TIOCGPTN, &n))
		goto fail;
	if (!name)
		name = buf;
	snprintf(name, sizeof buf, "/dev/pts/%d", n);
	int s = open(name, O_RDWR | O_NOCTTY);
	if (s < 0)
		goto fail;
	if (tio)
		tcsetattr(s, TCSANOW, tio);
	if (ws)
		ioctl(s, TIOCSWINSZ, ws);
	*pm = m;
	*ps = s;
	return 0;
fail:
	close(m);
	return -1;
}

int login_tty(int fd)
{
	setsid();
	if (ioctl(fd, TIOCSCTTY, 0))
		return -1;
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);
	return 0;
}

int forkpty(int *pm, char *name, const struct termios *tio,
	const struct winsize *ws)
{
	int m, s;
	if (openpty(&m, &s, name, tio, ws) < 0)
		return -1;
	pid_t pid = fork();
	if (!pid) {
		close(m);
		if (login_tty(s))
			_exit(127);
		return 0;
	}
	close(s);
	if (pid < 0)
		close(m);
	else
		*pm = m;
	return pid;
}
