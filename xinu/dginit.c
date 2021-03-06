#include "conf.h"
#include "kernel.h"
#include "network.h"

struct dgblk dgtab[Ndg];	// dg device control blocks

//------------------------------------------------------------------------
//  dginit  -  initialize datagram protocol pseudo device marking it free
//------------------------------------------------------------------------
void
dginit(struct devsw *devptr)
{
	struct dgblk *dgptr;

	devptr->iobuf = (char *)(dgptr = &dgtab[devptr->minor]);
	dgptr->dg_dnum = devptr->num;
	dgptr->dg_state = DG_FREE;
}
