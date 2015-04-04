#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sem.h"

//------------------------------------------------------------------------
// newsem  --  allocate an unused semaphore and return its index
//------------------------------------------------------------------------
static int
newsem(void)
{

	for (int i = 0; i < NSEM; i++) {
		int sem = nextsem--;
		if (nextsem < 0)
			nextsem = NSEM - 1;
		if (semaph[sem].sstate == SFREE) {
			semaph[sem].sstate = SUSED;
			return sem;
		}
	}

	return SYSERR;
}

//------------------------------------------------------------------------
// screate  --  create and initialize a semaphore, returning its id
// Initial count is >= 0.
//------------------------------------------------------------------------
SYSCALL
screate(int count)
{
	char ps;
	int sem;

	disable(ps);
	if (count < 0 || (sem = newsem()) == SYSERR) {
		restore(ps);
		return SYSERR;
	}
	semaph[sem].semcnt = count;
	// sqhead and sqtail were initialized at system startup
	restore(ps);

	return sem;
}
