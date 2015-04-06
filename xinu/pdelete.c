#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "ports.h"

//------------------------------------------------------------------------
//  pdelete  --  delete a port, freeing waiting processes and messages
//------------------------------------------------------------------------
SYSCALL
pdelete(int portid, int (*dispose)(void *))
{
	int ps;
	struct pt *ptptr;

	ps = disable();
	if (isbadport(portid) ||
	    unmarked(ptmark) ||
	    (ptptr = &ports[portid])->ptstate != PTALLOC) {
		restore(ps);
		return SYSERR;
	}
	_ptclear(ptptr, PTFREE, dispose);
	restore(ps);

	return OK;
}
