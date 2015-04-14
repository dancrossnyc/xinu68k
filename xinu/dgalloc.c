#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  dgalloc  -  allocate a datagram psuedo device and return descriptor
//------------------------------------------------------------------------
int
dgalloc(void)
{
	int ps = disable();

	for (int k = 0; k < Ndg; k++) {
		struct dgblk *dgptr = &dgtab[k];
		if (dgptr->dg_state == DG_FREE) {
			dgptr->dg_state = DG_USED;
			restore(ps);
			return k;
		}
	}
	restore(ps);

	return SYSERR;
}
