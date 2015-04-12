#include "conf.h"
#include "kernel.h"
#include "disk.h"
#include "lfile.h"

#ifndef	Ndf
#define	Ndf	1
#endif
struct flblk fltab[Ndf];

//------------------------------------------------------------------------
//  lfinit  --  mark disk file 'device' available at system startup
//------------------------------------------------------------------------
int
lfinit(struct devsw *devptr)
{
	struct flblk *flptr;

	flptr = &fltab[devptr->minor];
	devptr->iobuf = (void *)flptr;
	flptr->fl_pid = 0;
	flptr->fl_id = devptr->num;

	return OK;
}
