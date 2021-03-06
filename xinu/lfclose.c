#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"
#include "lfile.h"
#include "dir.h"

//------------------------------------------------------------------------
//  lfclose  --  close a file by flushing output and freeing device slot
//------------------------------------------------------------------------
int
lfclose(struct devsw *devptr)
{
	struct dsblk *dsptr;
	struct dir *dirptr;
	struct flblk *flptr;
	int diskdev;
	int ps;

	ps = disable();
	flptr = (struct flblk *)devptr->iobuf;
	if (flptr->fl_pid != currpid) {
		restore(ps);
		return SYSERR;
	}
	diskdev = flptr->fl_dev;
	dsptr = (struct dsblk *)devtab[diskdev].iobuf;
	dirptr = (struct dir *)dsptr->ddir;
	if ((flptr->fl_mode & FLWRITE) && flptr->fl_dch)
		lfsflush(flptr);
	flptr->fl_pid = 0;
	dsptr->dnfiles--;
	write(diskdev, dskbcpy(dirptr), DIRBLK);
	restore(ps);
	return OK;
}
