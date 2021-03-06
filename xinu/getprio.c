#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
// getprio -- return the scheduling priority of a given process
//------------------------------------------------------------------------
SYSCALL
getprio(int pid)
{
	struct pentry *pptr;
	int ps;

	ps = disable();
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return SYSERR;
	}
	restore(ps);
	return pptr->pprio;
}
