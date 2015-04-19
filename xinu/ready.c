#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"

//------------------------------------------------------------------------
// ready  --  make a process eligible for CPU service
//
//   pid: id of process to make ready
//   resch: reschedule afterward?
//------------------------------------------------------------------------
int
ready(int pid)
{
	struct pentry *pptr;

	if (isbadpid(pid))
		return SYSERR;
	pptr = &proctab[pid];
	pptr->pstate = PRREADY;
	insert(pid, rdyhead, pptr->pprio);

	return OK;
}

int
readysched(int pid)
{
	if (ready(pid) != OK)
		return SYSERR;
	resched();

	return OK;
}
