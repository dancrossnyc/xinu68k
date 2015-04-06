#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sem.h"

//------------------------------------------------------------------------
//  sreset  --  reset the count and queue of a semaphore
//------------------------------------------------------------------------
SYSCALL
sreset(int sem, int count)
{
	struct sentry *sptr;
	int ps;
	int pid;
	int slist;

	ps = disable();
	if (isbadsem(sem) || count < 0 || semaph[sem].sstate == SFREE) {
		restore(ps);
		return SYSERR;
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid = getfirst(slist)) != EMPTY)
		ready(pid, RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);

	return OK;
}
