#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  dgcntl  -  control function for datagram pseudo-devices
//------------------------------------------------------------------------
int
dgcntl(struct devsw *devptr, int func, int arg)
{
	struct dgblk *dgptr;
	int freebuf();
	int ps;
	int ret;

	ps = disable();
	dgptr = (struct dgblk *)devptr->iobuf;
	ret = OK;
	switch (func) {

	case DG_SETMODE:	// set mode bits
		dgptr->dg_mode = arg;
		break;

	case DG_CLEAR:		// clear queued packets
		preset(dgptr->dg_xport, freebuf);
		break;

	default:
		ret = SYSERR;
	}
	restore(ps);
	return ret;
}
