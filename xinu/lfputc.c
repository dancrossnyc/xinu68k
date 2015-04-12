#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"
#include "lfile.h"
#include "dir.h"

//------------------------------------------------------------------------
//  lfputc  --  put a character onto a (buffered) disk file
//------------------------------------------------------------------------
int
lfputc(struct devsw *devptr, int ch)
{
	struct flblk *flptr;
	int ps;

	ps = disable();
	flptr = (struct flblk *)devptr->iobuf;
	if (flptr->fl_pid != currpid || !(flptr->fl_mode & FLWRITE)) {
		restore(ps);
		return SYSERR;
	}
	if (flptr->fl_bptr >= &flptr->fl_buff[DBUFSIZ]) {
		if (flptr->fl_dch)
			lfsflush(flptr);
		lfsetup(flptr->fl_dev, flptr);
	}
	if (flptr->fl_pos >= (flptr->fl_dent)->fdlen)
		(flptr->fl_dent)->fdlen++;
	flptr->fl_pos++;
	*(flptr->fl_bptr)++ = ch;
	flptr->fl_dch = TRUE;
	restore(ps);
	return OK;
}
