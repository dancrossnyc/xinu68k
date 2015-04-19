#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sleep.h"

//------------------------------------------------------------------------
// sleep10  --  delay the caller for a time specified in tenths of seconds
//------------------------------------------------------------------------
SYSCALL
sleep10(int n)
{
	int ps;

	if (n < 0 || !hasclock)
		return SYSERR;
	ps = disable();
	if (n > 0) {		// sleep10(0) -> end time slice
		insertd(currpid, clockq, n);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
	restore(ps);

	return OK;
}
