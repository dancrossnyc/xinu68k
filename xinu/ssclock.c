#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sleep.h"

//------------------------------------------------------------------------
// stopclock -- put the clock in defer mode
//------------------------------------------------------------------------
void
stopclock(void)
{
	deferclock++;
}

//------------------------------------------------------------------------
// startclock -- take the clock out of defer mode
//------------------------------------------------------------------------
void
startclock(void)
{
	int ps;
	int makeup;
	int next;

	ps = disable();
	if (deferclock <= 0 || --deferclock > 0) {
		restore(ps);
		return;
	}
	makeup = clkdiff;
	preempt -= makeup;
	clkdiff = 0;
	if (slnempty) {
		for (next = firstid(clockq);
		     next < NPROC && q[next].qkey < makeup;
		     next = q[next].qnext) {
			makeup -= q[next].qkey;
			q[next].qkey = 0;
		}
		if (next < NPROC)
			q[next].qkey -= makeup;
		wakeup();
	}
	if (preempt <= 0)
		resched();
	restore(ps);
}
