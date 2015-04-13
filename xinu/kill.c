#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "sem.h"
#include "mem.h"
#include "io.h"

//------------------------------------------------------------------------
// kill  --  kill a process and remove it from the system
//
//	pid: process to kill
//------------------------------------------------------------------------
SYSCALL
kill(int pid)
{
	struct pentry *proc;	// points to process table for pid
	int dev;
	int ps;

	ps = disable();
	if (isbadpid(pid) || &proctab[pid]->pstate == PRFREE) {
		restore(ps);
		return SYSERR;
	}
	if (--numproc == 0)
		xdone();
	proc = &proctab[pid];
	dev = proc->pdevs[0];
	if (!isbaddev(dev))
		close(dev);
	dev = proc->pdevs[1];
	if (!isbaddev(dev))
		close(dev);
	send(proc->pnxtkin, pid);
	freestk(proc->pbase, proc->pstklen);
	switch (proc->pstate) {
	case PRCURR:
		proc->pstate = PRFREE;	// suicide
		resched();
		break;			// Unreached.
	case PRWAIT:
		semaph[proc->psem].semcnt++;
		// fall through
	case PRREADY:
		dequeue(pid);
		proc->pstate = PRFREE;
		break;
	case PRSLEEP:
	case PRTRECV:
		unsleep(pid);
		// fall through
	default:
		proc->pstate = PRFREE;
	}
	restore(ps);

	return OK;
}
