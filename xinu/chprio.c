#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
// chprio  --  change the scheduling priority of a process
//
// newprio > 0.
//------------------------------------------------------------------------
SYSCALL
chprio(int pid, int newprio)
{
	int oldprio;
	struct pentry *pptr;
	uword ps;

	ps = disable();
	if (isbadpid(pid) || newprio <= 0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return SYSERR;
	}
	oldprio = pptr->pprio;
	pptr->pprio = newprio;
	switch (pptr->pstate) {
	case PRREADY:
		insert(dequeue(pid), rdyhead, newprio);
	case PRCURR:
		resched();
	default:
		break;
	}
	restore(ps);

	return oldprio;
}
