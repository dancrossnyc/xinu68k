#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sem.h"

//------------------------------------------------------------------------
// wait  --  make current process wait on a semaphore
//------------------------------------------------------------------------
SYSCALL
wait(int sem)
{
	int ps;
	struct sentry *sptr;
	struct pentry *pptr;

	ps = disable();
	if (isbadsem(sem) || (sptr = &semaph[sem])->sstate == SFREE) {
		restore(ps);
		return SYSERR;
	}
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid, sptr->sqtail);
		resched();
	}
	restore(ps);

	return OK;
}
