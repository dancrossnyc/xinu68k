#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"

//------------------------------------------------------------------------
//  dsread  --  read a block from a disk device
//------------------------------------------------------------------------
int
dsread(struct devsw *devptr, char *buff, DBADDR block)
{
	struct dreq *drptr;
	int stat;
	int ps;

	ps = disable();
	drptr = (struct dreq *)getbuf(dskrbp);
	drptr->drdba = block;
	drptr->drpid = currpid;
	drptr->drbuff = buff;
	drptr->drop = DREAD;
	if ((stat = dskenq(drptr, (struct dsblk *)devptr->dvioblk)) == DONQ) {
		suspend(currpid);
		stat = drptr->drstat;
	}
	freebuf(drptr);
	restore(ps);
	return stat;
}
