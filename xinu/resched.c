#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"

//------------------------------------------------------------------------
// resched  --  reschedule processor to highest priority ready process
//
// Notes:	Upon entry, currpid gives current process id.
//		Proctab[currpid].pstate gives correct NEXT state for
//			current process if other than PRCURR.
//------------------------------------------------------------------------
int
resched(void)
{
	struct pentry *optr;	// pointer to old process entry
	struct pentry *nptr;	// pointer to new process entry

	// no switch needed if current process priority higher than next
	if (((optr = &proctab[currpid])->pstate == PRCURR) &&
	    (lastkey(rdytail) < optr->pprio))
		return OK;

	// force context switch
	if (optr->pstate == PRCURR) {
		optr->pstate = PRREADY;
		insert(currpid, rdyhead, optr->pprio);
	}

	// remove highest priority process at end of ready list
	currpid = getlast(rdytail);
	nptr = &proctab[currpid];
	nptr->pstate = PRCURR;	// mark it currently running

	// Check the stack for corruption.
	if (*((uword *)nptr->pbase) != MAGIC) {
		kprintf("Bad magic pid=%d, value=%o, at %o\n",
			currpid, *((int *)nptr->pbase), nptr->pbase);
		panic("stack corrupted");
	}
	if (nptr->pregs[SP] < (uintptr_t)nptr->plimit) {
		kprintf("Bad SP pid=%d (%s), lim=%o will be %o\n",
			currpid, nptr->pname, nptr->plimit,
			nptr->pregs[SP]);
		panic("stack overflow");
	}

	preempt = QUANTUM;	// reset preemption counter

kprintf("Coroutine jump!\n");
	// Coroutine jump.
	ctxsw(optr->pregs, nptr->pregs);

	// The OLD process returns here when resumed.
	return OK;
}
