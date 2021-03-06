#include "conf.h"
#include "kernel.h"
#include "disk.h"

struct dsblk dstab[Ndsk];
int dskdbp, dskrbp;

//------------------------------------------------------------------------
//  dsinit  --  initialize disk drive device
//------------------------------------------------------------------------
void
dsinit(struct devsw *devptr)
{
	struct dsblk *dsptr;
	struct dtc *dtptr;
	int status;
	int ps;

	ps = disable();
	devptr->iobuf = (char *)(dsptr = &dstab[devptr->minor]);
	dsptr->dcsr = (struct dtc *)devptr->csr;
	dsptr->dreqlst = DRNULL;
	dsptr->dnum = devptr->num;
	dsptr->dibsem = screate(1);
	dsptr->dflsem = screate(1);
	dsptr->ddirsem = screate(1);
	dsptr->dnfiles = 0;
	dsptr->ddir = getbuf(dskdbp);
	//iosetvec(devptr->num, dsptr, dsptr);

	// read directory block: setup read command then start interface

	dsptr->ddcb.xop = (char) XOREAD;
	dsptr->ddcb.xunit = (char) 0;
	dsptr->ddcb.xcntl = (char) XRETRY;
	dsptr->ddcb.xmaddr = (char) ((DIRBLK >> 8) & 0xFF);
	dsptr->ddcb.xladdr = (char) (DIRBLK & 0xFF);
	dsptr->ddcb.xcount = (char) 1;
	dtptr = dsptr->dcsr;
	dtptr->dt_dar = dsptr->ddir;
	dtptr->dt_car = &dsptr->ddcb;
	dtptr->dt_xdar = NULL;
	dtptr->dt_xcar = NULL;
	dtptr->dt_csr = DTGO;
	//while (((status = dtptr->dt_csr) & DTDONE) == 0);	// XXX Hack for simulator.
	status = 0;
	if (status & DTERROR)
		panic("Disk error");
	restore(ps);
}
