#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
//  dgclose  -  close a datagram pseudo device, making it available again
//------------------------------------------------------------------------
int
dgclose(struct devsw *devptr)
{
	int ps;
	struct dgblk *dgptr;
	struct netq *nqptr;
	int nq;

	dgptr = (struct dgblk *)devptr->iobuf;
	ps = disable();
	nq = dgptr->dg_netq;
	nqptr = &Net.netqs[nq];
	nqptr->valid = FALSE;
	nqptr->uport = -1;
	nqptr->pid = BADPID;
	dgptr->dg_state = DG_FREE;
	restore(ps);

	return OK;
}
