#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  dgalloc  -  allocate a datagram psuedo device and return descriptor
//------------------------------------------------------------------------
int
dgalloc(void)
{
	struct dgblk *dgptr;
	int i;
	char ps;

	disable(ps);
	for (i = 0; i < Ndg; i++) {
		dgptr = &dgtab[i];
		if (dgptr->dg_state == DG_FREE) {
			dgptr->dg_state = DG_USED;
			restore(ps);
			return i;
		}
	}
	restore(ps);

	return SYSERR;
}
