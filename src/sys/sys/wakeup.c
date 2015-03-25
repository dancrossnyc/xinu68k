/* wakeup.c - wakeup */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>

/*------------------------------------------------------------------------
 * wakeup  --  called by clock interrupt dispatcher to awaken processes
 *------------------------------------------------------------------------
 */
INTPROC
wakeup(void)
{
	while (nonempty(clockq) && firstkey(clockq) <= 0)
		ready(getfirst(clockq), RESCHNO);
	if ((slnempty = nonempty(clockq)) != 0)
		sltop = (int *) &q[q[clockq].qnext].qkey;
	resched();
}
