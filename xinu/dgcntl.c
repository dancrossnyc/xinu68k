#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  dgcntl  -  control function for datagram pseudo-devices
//------------------------------------------------------------------------
int
dgcntl(struct devsw *devptr, int func, int arg)
{
	int ps = disable();
	struct dgblk *dgptr = (struct dgblk *)devptr->iobuf;

	switch (func) {
	case DG_SETMODE:	// set mode bits
		dgptr->dg_mode = arg;
		break;
	case DG_CLEAR:		// clear queued packets
		preset(dgptr->dg_xport, freebuf);
		break;
	default:
		restore(ps);
		return SYSERR;
	}
	restore(ps);

	return OK;
}
