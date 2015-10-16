#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sleep.h"

//------------------------------------------------------------------------
// recvtime - wait to receive a message or timeout and return result
//------------------------------------------------------------------------
SYSCALL
recvtime(int maxwait)
{
	struct pentry *pptr;
	int msg;
	int ps;

	if (maxwait < 0 || !hasclock)
		return SYSERR;
	ps = disable();
	pptr = &proctab[currpid];
	if (!pptr->phasmsg) {	// if no message, wait
		insertd(currpid, clockq, maxwait);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
		pptr->pstate = PRTRECV;
		resched();
	}
	msg = TIMEOUT;
	if (pptr->phasmsg) {
		msg = pptr->pmsg;	// msg. arrived => retrieve it
		pptr->phasmsg = FALSE;
	}
	restore(ps);

	return msg;
}
