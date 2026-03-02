#ifndef _PWD_H
#define _PWD_H
#include <sys/types.h>
struct passwd {
	char *pw_name, *pw_passwd; uid_t pw_uid; gid_t pw_gid;
	char *pw_gecos, *pw_dir, *pw_shell;
};
struct passwd *getpwnam(const char *);
struct passwd *getpwuid(uid_t);
struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);
int getpwnam_r(const char *, struct passwd *, char *, size_t, struct passwd **);
int getpwuid_r(uid_t, struct passwd *, char *, size_t, struct passwd **);
#endif
