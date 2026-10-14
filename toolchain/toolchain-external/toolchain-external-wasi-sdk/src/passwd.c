// Replacement user and group database functions, which wasi-libc lacks. They
// read /etc/passwd and /etc/group as musl does, so names and memberships come
// from the files of the root filesystem. Each lookup reads its own copy of
// the file, so it does not disturb a getpwent or getgrent walk.

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setgroups(size_t, const gid_t *);

// The entry most recently returned, which points into its line buffer.
static struct passwd pw;
static struct group gr;
static char *pw_line, *gr_line;
static size_t pw_size, gr_size;
static char **gr_mem;
static size_t gr_nmem;

// The files the getpwent and getgrent walks read.
static FILE *pw_walk, *gr_walk;

// field cuts the string at *s at the next delim and advances *s past it.
static char *field(char **s, int delim)
{
	char *start = *s, *end = strchr(start, delim);
	if (end) {
		*end = 0;
		*s = end + 1;
	} else {
		*s = start + strlen(start);
	}
	return start;
}

// number parses a decimal ID, returning 0 when s is not one.
static int number(const char *s, unsigned *id)
{
	char *end;
	if (!*s) return 0;
	*id = strtoul(s, &end, 10);
	return !*end;
}

// parse_pw fills pw from an /etc/passwd line, returning 0 for a malformed one.
static int parse_pw(char *s)
{
	unsigned uid, gid;
	s[strcspn(s, "\n")] = 0;
	pw.pw_name = field(&s, ':');
	pw.pw_passwd = field(&s, ':');
	if (!number(field(&s, ':'), &uid) || !number(field(&s, ':'), &gid)) return 0;
	pw.pw_uid = uid;
	pw.pw_gid = gid;
	pw.pw_gecos = field(&s, ':');
	pw.pw_dir = field(&s, ':');
	pw.pw_shell = field(&s, ':');
	return *pw.pw_name != 0;
}

// parse_gr fills gr from an /etc/group line, returning 0 for a malformed one.
static int parse_gr(char *s)
{
	// Split the fixed fields.
	unsigned gid;
	size_t n = 0;
	s[strcspn(s, "\n")] = 0;
	gr.gr_name = field(&s, ':');
	gr.gr_passwd = field(&s, ':');
	if (!number(field(&s, ':'), &gid) || !*gr.gr_name) return 0;
	gr.gr_gid = gid;

	// Split the comma-separated members into a null-terminated list.
	for (char *m = s; *m; n++) field(&m, ',');
	if (n + 1 > gr_nmem) {
		char **mem = realloc(gr_mem, (n + 1) * sizeof *mem);
		if (!mem) return 0;
		gr_mem = mem;
		gr_nmem = n + 1;
	}
	for (size_t i = 0; i < n; i++) {
		gr_mem[i] = s;
		s += strlen(s) + 1;
	}
	gr_mem[n] = 0;
	gr.gr_mem = gr_mem;
	return 1;
}

// next_pw reads the next well-formed entry of f.
static struct passwd *next_pw(FILE *f)
{
	while (f && getline(&pw_line, &pw_size, f) >= 0) {
		if (parse_pw(pw_line)) return &pw;
	}
	return 0;
}

// next_gr reads the next well-formed entry of f.
static struct group *next_gr(FILE *f)
{
	while (f && getline(&gr_line, &gr_size, f) >= 0) {
		if (parse_gr(gr_line)) return &gr;
	}
	return 0;
}

// find_pw returns the entry named name, or with uid when name is null.
static struct passwd *find_pw(const char *name, uid_t uid)
{
	FILE *f = fopen("/etc/passwd", "r");
	struct passwd *p;
	while ((p = next_pw(f)) && (name ? strcmp(p->pw_name, name) : p->pw_uid != uid))
		;
	if (f) fclose(f);
	return p;
}

// find_gr returns the group named name, or with gid when name is null.
static struct group *find_gr(const char *name, gid_t gid)
{
	FILE *f = fopen("/etc/group", "r");
	struct group *g;
	while ((g = next_gr(f)) && (name ? strcmp(g->gr_name, name) : g->gr_gid != gid))
		;
	if (f) fclose(f);
	return g;
}

void setpwent(void)
{
	if (pw_walk) rewind(pw_walk);
}

void endpwent(void)
{
	if (pw_walk) fclose(pw_walk);
	pw_walk = 0;
}

struct passwd *getpwent(void)
{
	if (!pw_walk) pw_walk = fopen("/etc/passwd", "r");
	return next_pw(pw_walk);
}

struct passwd *getpwnam(const char *name)
{
	return find_pw(name, 0);
}

struct passwd *getpwuid(uid_t uid)
{
	return find_pw(0, uid);
}

// copy_pw copies the entry found into buf for the reentrant lookups.
static int copy_pw(struct passwd *found, struct passwd *p, char *buf, size_t size, struct passwd **res)
{
	// Report a missing entry as success with no result, as POSIX does.
	char **dst[] = {&p->pw_name, &p->pw_passwd, &p->pw_gecos, &p->pw_dir, &p->pw_shell};
	char *src[5];
	*res = 0;
	if (!found) return 0;

	// Copy each string, then the IDs.
	src[0] = found->pw_name, src[1] = found->pw_passwd, src[2] = found->pw_gecos;
	src[3] = found->pw_dir, src[4] = found->pw_shell;
	for (int i = 0; i < 5; i++) {
		size_t n = strlen(src[i]) + 1;
		if (n > size) return ERANGE;
		*dst[i] = memcpy(buf, src[i], n);
		buf += n;
		size -= n;
	}
	p->pw_uid = found->pw_uid;
	p->pw_gid = found->pw_gid;
	*res = p;
	return 0;
}

int getpwnam_r(const char *name, struct passwd *p, char *buf, size_t size, struct passwd **res)
{
	return copy_pw(find_pw(name, 0), p, buf, size, res);
}

int getpwuid_r(uid_t uid, struct passwd *p, char *buf, size_t size, struct passwd **res)
{
	return copy_pw(find_pw(0, uid), p, buf, size, res);
}

void setgrent(void)
{
	if (gr_walk) rewind(gr_walk);
}

void endgrent(void)
{
	if (gr_walk) fclose(gr_walk);
	gr_walk = 0;
}

struct group *getgrent(void)
{
	if (!gr_walk) gr_walk = fopen("/etc/group", "r");
	return next_gr(gr_walk);
}

struct group *getgrnam(const char *name)
{
	return find_gr(name, 0);
}

struct group *getgrgid(gid_t gid)
{
	return find_gr(0, gid);
}

// copy_gr copies the group found into buf for the reentrant lookups: the
// member list first, aligned for its pointers, then each string.
static int copy_gr(struct group *found, struct group *g, char *buf, size_t size, struct group **res)
{
	// Report a missing group as success with no result, as POSIX does.
	size_t n = 0, pad = -(uintptr_t)buf % sizeof(char *);
	*res = 0;
	if (!found) return 0;

	// Place the member list.
	while (found->gr_mem[n]) n++;
	if (pad + (n + 1) * sizeof(char *) > size) return ERANGE;
	g->gr_mem = (char **)(buf + pad);
	buf += pad + (n + 1) * sizeof(char *);
	size -= pad + (n + 1) * sizeof(char *);

	// Copy the name, the password and the members.
	for (size_t i = 0; i < n + 2; i++) {
		char *src = i == 0 ? found->gr_name : i == 1 ? found->gr_passwd : found->gr_mem[i - 2];
		size_t len = strlen(src) + 1;
		if (len > size) return ERANGE;
		memcpy(buf, src, len);
		if (i == 0) g->gr_name = buf;
		else if (i == 1) g->gr_passwd = buf;
		else g->gr_mem[i - 2] = buf;
		buf += len;
		size -= len;
	}
	g->gr_mem[n] = 0;
	g->gr_gid = found->gr_gid;
	*res = g;
	return 0;
}

int getgrnam_r(const char *name, struct group *g, char *buf, size_t size, struct group **res)
{
	return copy_gr(find_gr(name, 0), g, buf, size, res);
}

int getgrgid_r(gid_t gid, struct group *g, char *buf, size_t size, struct group **res)
{
	return copy_gr(find_gr(0, gid), g, buf, size, res);
}

// getgrouplist stores gid and the groups listing user as a member. When more
// than *ngroups groups match, it stores the first *ngroups, sets *ngroups to
// the count and returns -1, as glibc does.
int getgrouplist(const char *user, gid_t gid, gid_t *groups, int *ngroups)
{
	// Collect gid, then each other group naming user.
	FILE *f = fopen("/etc/group", "r");
	struct group *g;
	int n = 0;
	if (n < *ngroups) groups[n] = gid;
	n++;
	while ((g = next_gr(f))) {
		if (g->gr_gid == gid) continue;
		for (char **m = g->gr_mem; *m; m++) {
			if (strcmp(*m, user)) continue;
			if (n < *ngroups) groups[n] = g->gr_gid;
			n++;
			break;
		}
	}
	if (f) fclose(f);

	// Report the count.
	int fit = n <= *ngroups;
	*ngroups = n;
	return fit ? n : -1;
}

// initgroups sets the supplementary groups to those getgrouplist finds.
int initgroups(const char *user, gid_t gid)
{
	gid_t groups[64];
	int n = sizeof groups / sizeof *groups;
	if (getgrouplist(user, gid, groups, &n) < 0) {
		errno = EINVAL;
		return -1;
	}
	return setgroups(n, groups);
}
