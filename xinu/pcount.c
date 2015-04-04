#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "ports.h"

//------------------------------------------------------------------------
//  pcount  --  return the count of current messages in a port
//------------------------------------------------------------------------
SYSCALL
pcount(int portid)
{
	int scnt;
	int count;
	char ps;
	struct pt *ptptr;

	disable(ps);
	if (isbadport(portid) ||
	    unmarked(ptmark) ||
	    (ptptr = &ports[portid])->ptstate != PTALLOC) {
		restore(ps);
		return SYSERR;
	}
	count = scount(ptptr->ptrsem);
	if ((scnt = scount(ptptr->ptssem)) < 0)
		count -= scnt;	// add number waiting
	restore(ps);

	return count;
}
