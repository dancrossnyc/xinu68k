#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
//  receive  -  wait for a message and return it
//------------------------------------------------------------------------
SYSCALL
receive(void)
{
	struct pentry *pptr;
	int msg;
	int ps;

	ps = disable();
	pptr = &proctab[currpid];
	if (!pptr->phasmsg) {	// if no message, wait for one
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;	// retrieve message
	pptr->phasmsg = FALSE;
	restore(ps);
	return msg;
}
