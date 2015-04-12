#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"

//------------------------------------------------------------------------
//  dswrite  --  write a block (system buffer) onto a disk device
//------------------------------------------------------------------------
int
dswrite(struct devsw *devptr, char *buff, DBADDR block)
{
	struct dreq *drptr;
	int ps;

	ps = disable();
	drptr = (struct dreq *)getbuf(dskrbp);
	drptr->drbuff = buff;
	drptr->drdba = block;
	drptr->drpid = currpid;
	drptr->drop = DWRITE;
	dskenq(drptr, (struct dsblk *)devptr->iobuf);
	restore(ps);
	return OK;
}
