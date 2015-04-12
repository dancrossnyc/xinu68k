#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  seek  --  position a device (very common special case of control)
//------------------------------------------------------------------------
SYSCALL
seek(int descrp, long pos)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return SYSERR;
	devptr = &devtab[descrp];

	return (*devptr->seek)(devptr, pos);
}
