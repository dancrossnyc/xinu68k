#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "mem.h"
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
addarg(int pid, int nargs, size_t len)
{
	struct pentry *pptr;
	uintptr_t *toarg;
	char *to;

	if (isbadpid(pid) || proctab[pid].pstate != PRSUSP)
		return SYSERR;
	pptr = &proctab[pid];
	toarg = (uintptr_t *)((uintptr_t)pptr->pbase - (size_t)roundew(len));
	to = (char *)(toarg + nargs + 2);
	*toarg = (uintptr_t)(toarg + 1);
	toarg++;
	for (char **fromarg = Shl.shtok; nargs-- > 0;
	     toarg++, fromarg++, to += strlen(to) + 1)
	{
		size_t size = strlen(*fromarg) + 1;
		*toarg = (uintptr_t)to;
		strlcpy(to, *fromarg, size);
	}
	*toarg = (uintptr_t)NULL;

	return OK;
}
