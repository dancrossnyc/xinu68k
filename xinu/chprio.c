#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
// chprio  --  change the scheduling priority of a process
//
//	newprio > 0.
//------------------------------------------------------------------------
SYSCALL
chprio(int pid, int newprio)
{
	int oldprio;
	struct pentry *proc;
	int ps;

	ps = disable();
	if (isbadpid(pid) || newprio <= 0 || proctab[pid].pstate == PRFREE) {
		restore(ps);
		return SYSERR;
	}
	proc = &proctab[pid];
	oldprio = proc->pprio;
	proc->pprio = newprio;
	switch (proc->pstate) {
	case PRREADY:
		insert(dequeue(pid), rdyhead, newprio);
		// FALLTHROUGH
	case PRCURR:
		resched();
		// FALLTHROUGH
	default:
		break;
	}
	restore(ps);

	return oldprio;
}
