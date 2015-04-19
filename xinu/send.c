#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
//  send  --  send a message to another process
//------------------------------------------------------------------------
SYSCALL
send(int pid, int msg)
{
	struct pentry *pptr;	// receiver's proc. table addr.
	int ps;

	ps = disable();
	if (isbadpid(pid) ||
            ((pptr = &proctab[pid])->pstate == PRFREE) ||
            pptr->phasmsg) {
		restore(ps);
		return SYSERR;
	}
	pptr->pmsg = msg;	// deposit message
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	// if receiver waits, start it
		readysched(pid);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		readysched(pid);
	}
	restore(ps);

	return OK;
}
