// addarg.c - addarg

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <shell.h>

//------------------------------------------------------------------------
//  addarg  -  copy arguments to area reserved on process stack
//------------------------------------------------------------------------
// pid: process to receive arguments
// nargs: number of arguments to copy
// len: size of arg. area (in bytes)
int
addarg(int pid, int nargs, int len)
{
	struct	pentry	*pptr;
	char	**fromarg;
	int	*toarg;
	char	*to;

	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate != PRSUSP)
		return(SYSERR);
	toarg = (int *)(((unsigned)pptr->pbase) - (unsigned)len);
	to = (char *) (toarg + (nargs + 2));
	*toarg = (int) (toarg + 1);
	toarg++;
	for (fromarg=Shl.shtok ; nargs > 0 ; nargs--) {
		*toarg++ = (int)to;
		strcpy(to, *fromarg++);
		to += strlen(to) + 1;
	}
	*toarg = 0;
	return(OK);
}
