#include "conf.h"
#include "kernel.h"
#include "proc.h"

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL
recvclr(void)
{
	char ps;
	int msg = OK;

	disable(ps);
	if (proctab[currpid].phasmsg) {	// existing message?
		proctab[currpid].phasmsg = FALSE;
		msg = proctab[currpid].pmsg;
	}
	restore(ps);

	return msg;
}
