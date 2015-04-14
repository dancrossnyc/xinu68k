#include "conf.h"
#include "kernel.h"
#include "disk.h"
#include "lfile.h"
#include "dir.h"

//------------------------------------------------------------------------
//  dsopen  --  open/create a file on the specified disk device
//------------------------------------------------------------------------
int
dsopen(struct devsw *devptr, char *filename, char *mode)
{
	//struct dir *dirptr;
	struct flblk *flptr;
	struct fdes *fdptr;
	DBADDR dba;
	int mbits, findex;
	int retcode;
	int ps;

	ps = disable();
	//dirptr = dsdirec(devptr->num);
	if ((mbits = ckmode(mode)) == SYSERR ||
	    (fdptr = dfdsrch((struct dsblk *)devptr->iobuf, filename, mbits)) == (struct fdes *)SYSERR ||
	    (findex = dfalloc()) == SYSERR) {
		restore(ps);
		return SYSERR;
	}
	flptr = &fltab[findex];
	flptr->fl_dev = devptr->num;
	flptr->fl_dent = fdptr;
	flptr->fl_mode = mbits & FLRW;
	flptr->fl_iba = fdptr->fdiba;
	ibget(flptr->fl_dev, flptr->fl_iba, &(flptr->fl_iblk));
	flptr->fl_pos = 0L;
	flptr->fl_dch = FALSE;
	dba = flptr->fl_iblk.ib_dba[flptr->fl_ipnum = 0];
	if (dba != DBNULL) {
		read(flptr->fl_dev, flptr->fl_buff, dba);
		flptr->fl_bptr = flptr->fl_buff;
	} else
		flptr->fl_bptr = &flptr->fl_buff[DBUFSIZ];
	retcode = flptr->fl_id;
	restore(ps);

	return retcode;
}
