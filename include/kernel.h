#include "u.h"

extern int rdyhead, rdytail;
extern int preempt;

#include "fns.h"

int atoi(const char *s);
int fprintf(int dev, const char *fmt, ...);
int printf(const char *fmt, ...);
int write(int descrp, const void *buff, int count);
