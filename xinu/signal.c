#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sem.h"

//------------------------------------------------------------------------
// signal  --  signal a semaphore, releasing one waiting process
//------------------------------------------------------------------------
SYSCALL
signal(int sem)
{
	struct sentry *sptr;
	int ps;

	ps = disable();
	if (isbadsem(sem) || (sptr = &semaph[sem])->sstate == SFREE) {
		restore(ps);
		return SYSERR;
	}
	if ((sptr->semcnt++) < 0)
		readysched(getfirst(sptr->sqhead));
	restore(ps);

	return OK;
}
