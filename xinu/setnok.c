#include "conf.h"
#include "kernel.h"
#include "proc.h"

//------------------------------------------------------------------------
//  setnok  -  set next-of-kin (notified at death) for a given process
//------------------------------------------------------------------------
SYSCALL
setnok(int nok, int pid)
{
	int ps;
	struct pentry *pptr;

	ps = disable();
	if (isbadpid(pid)) {
		restore(ps);
		return SYSERR;
	}
	pptr = &proctab[pid];
	pptr->pnxtkin = nok;
	restore(ps);

	return OK;
}
