#ifndef _MNTENT_H
#define _MNTENT_H

#include <stdio.h>

struct mntent {
    char *mnt_fsname;
    char *mnt_dir;
    char *mnt_type;
    char *mnt_opts;
    int mnt_freq;
    int mnt_passno;
};

FILE *setmntent(const char *filename, const char *type);
struct mntent *getmntent(FILE *fp);
struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen);
int addmntent(FILE *fp, const struct mntent *mnt);
int endmntent(FILE *fp);
char *hasmntopt(const struct mntent *mnt, const char *opt);

#endif
