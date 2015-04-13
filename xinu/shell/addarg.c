#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "shell.h"

//------------------------------------------------------------------------
//  addarg  -  copy arguments to area reserved on process stack
//
//      pid: process to receive arguments
//      nargs: number of arguments to copy
//      len: size of arg. area (in bytes)
//------------------------------------------------------------------------
int
addarg(int pid, int nargs, int len)
{
	struct pentry *pptr;
	char **fromarg;
	uintptr_t *toarg;
	char *to;

	if (isbadpid(pid) || proctab[pid].pstate != PRSUSP)
		return SYSERR;
	pptr = &proctab[pid];
	toarg = (uintptr_t *)((uintptr_t)pptr->pbase - (uintptr_t)len);
	to = (char *)(toarg + nargs + 2);
	*toarg = (uintptr_t)(toarg + 1);
	toarg++;
	for (fromarg = Shl.shtok; nargs > 0; nargs--) {
		*toarg++ = (uintptr_t)to;
		strcpy(to, *fromarg++);
		to += strlen(to) + 1;
	}
	*toarg = 0;

	return OK;
}
