#ifndef _SHADOW_H
#define _SHADOW_H

#include <stddef.h>

struct spwd {
    char *sp_namp;
    char *sp_pwdp;
    long sp_lstchg;
    long sp_min;
    long sp_max;
    long sp_warn;
    long sp_inact;
    long sp_expire;
    unsigned long sp_flag;
};

struct spwd *getspnam(const char *name);
struct spwd *getspent(void);
void setspent(void);
void endspent(void);
int putspent(const struct spwd *p, FILE *fp);
int lckpwdf(void);
int ulckpwdf(void);

#endif
