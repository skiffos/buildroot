// Replacement popen, pclose and system, which wasi-libc lacks, after musl
// (MIT license). Each forks a child that runs the command with /bin/sh -c;
// musl spawns it with posix_spawn, which wasi-libc also lacks.

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

// pipes records the open popen streams and their children. A child closes
// the other streams' descriptors, as Linux requires.
static struct pipe_entry {
	FILE *f;
	pid_t pid;
	struct pipe_entry *next;
} *pipes;

// shell runs cmd in a forked child and does not return.
static _Noreturn void shell(const char *cmd)
{
	char *argv[] = {"sh", "-c", (char *)cmd, 0};

	execve("/bin/sh", argv, environ);
	_exit(127);
}

FILE *popen(const char *cmd, const char *mode)
{
	struct pipe_entry *e, *l;
	int p[2], op;
	pid_t pid;

	if (*mode == 'r') {
		op = 0;
	} else if (*mode == 'w') {
		op = 1;
	} else {
		errno = EINVAL;
		return 0;
	}
	if (!(e = malloc(sizeof *e)))
		return 0;
	if (pipe(p)) {
		free(e);
		return 0;
	}
	if (!(e->f = fdopen(p[op], mode))) {
		close(p[0]);
		close(p[1]);
		free(e);
		return 0;
	}

	pid = fork();
	if (pid < 0) {
		fclose(e->f);
		close(p[1 - op]);
		free(e);
		return 0;
	}
	if (pid == 0) {
		for (l = pipes; l; l = l->next)
			close(fileno(l->f));
		close(p[op]);
		if (p[1 - op] != 1 - op) {
			dup2(p[1 - op], 1 - op);
			close(p[1 - op]);
		}
		shell(cmd);
	}

	close(p[1 - op]);
	e->pid = pid;
	e->next = pipes;
	pipes = e;
	return e->f;
}

int pclose(FILE *f)
{
	struct pipe_entry **l, *e;
	pid_t pid, r;
	int status;

	for (l = &pipes; *l && (*l)->f != f; l = &(*l)->next)
		;
	if (!(e = *l)) {
		errno = ECHILD;
		return -1;
	}
	*l = e->next;
	pid = e->pid;
	free(e);

	fclose(f);
	while ((r = waitpid(pid, &status, 0)) < 0 && errno == EINTR)
		;
	if (r < 0)
		return -1;
	return status;
}

int system(const char *cmd)
{
	struct sigaction sa = {.sa_handler = SIG_IGN}, oldint, oldquit;
	sigset_t mask, old;
	pid_t pid;
	int status = -1, r;

	if (!cmd)
		return 1;

	// The caller ignores the terminal's signals and holds SIGCHLD while the
	// command runs; the child restores both.
	sigaction(SIGINT, &sa, &oldint);
	sigaction(SIGQUIT, &sa, &oldquit);
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &mask, &old);

	pid = fork();
	if (pid == 0) {
		if (oldint.sa_handler != SIG_IGN)
			signal(SIGINT, SIG_DFL);
		if (oldquit.sa_handler != SIG_IGN)
			signal(SIGQUIT, SIG_DFL);
		sigprocmask(SIG_SETMASK, &old, 0);
		shell(cmd);
	}
	if (pid > 0) {
		while ((r = waitpid(pid, &status, 0)) < 0 && errno == EINTR)
			;
		if (r < 0)
			status = -1;
	}

	sigaction(SIGINT, &oldint, 0);
	sigaction(SIGQUIT, &oldquit, 0);
	sigprocmask(SIG_SETMASK, &old, 0);
	return status;
}
