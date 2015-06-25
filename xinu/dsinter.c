#include "conf.h"
#include "kernel.h"
#include "disk.h"

//------------------------------------------------------------------------
//  dsinter  --  process disk interrupt (DTC interface; XEBEC controller)
//------------------------------------------------------------------------
void
dsinter(struct dsblk *dsptr)
{
	struct dtc *dtptr;
	struct dreq *drptr;

	dtptr = dsptr->dcsr;
	drptr = dsptr->dreqlst;
	if (drptr == DRNULL) {
		panic("Disk interrupt when disk not busy");
		return;
	}
	drptr->drstat = OK;
	if (dtptr->dt_csr & DTERROR)
		drptr->drstat = SYSERR;
	if ((dsptr->dreqlst = drptr->drnext) != DRNULL)
		dskstart(dsptr);
	switch (drptr->drop) {
	case DREAD:
	case DSYNC:
		readysched(drptr->drpid);
		return;
	case DWRITE:
		freebuf(drptr->drbuff);
	case DSEEK:		// FALLTHROUGH
		freebuf(drptr);
	}
}
