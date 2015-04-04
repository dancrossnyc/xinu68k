#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sleep.h"

/*------------------------------------------------------------------------
 *  stopclk  --  put the clock in defer mode
 *------------------------------------------------------------------------
 */
void
stopclk(void)
{
	defclk++;
}

/*------------------------------------------------------------------------
 *  strtclk  --  take the clock out of defer mode
 *------------------------------------------------------------------------
 */
void
strtclk(void)
{
	char ps;
	int makeup;
	int next;

	disable(ps);
	if (defclk <= 0 || --defclk > 0) {
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
