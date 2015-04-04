#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"

/*------------------------------------------------------------------------
 * ready  --  make a process eligible for CPU service
 *
 *   pid: id of process to make ready
 *   resch: reschedule afterward?
 *------------------------------------------------------------------------
 */
int
ready(int pid, int resch)
{
	struct pentry *pptr;

	if (isbadpid(pid))
		return SYSERR;
	pptr = &proctab[pid];
	pptr->pstate = PRREADY;
	insert(pid, rdyhead, pptr->pprio);
	if (resch)
		resched();

	return OK;
}
