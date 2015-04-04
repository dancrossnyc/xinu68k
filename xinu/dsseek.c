#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"

//------------------------------------------------------------------------
//  dsseek  --  schedule a request to move the disk arm
//------------------------------------------------------------------------
int
dsseek(struct devsw *devptr, DBADDR block)
{
	struct dreq *drptr;
	char ps;

	disable(ps);
	drptr = (struct dreq *)getbuf(dskrbp);
	drptr->drdba = block;
	drptr->drpid = currpid;
	drptr->drbuff = NULL;
	drptr->drop = DSEEK;

	// enqueued with normal policy like other read/write requests
	dskenq(drptr, (struct dsblk *)devptr->dvioblk);
	restore(ps);
	return OK;
}
