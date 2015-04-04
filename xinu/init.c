#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  init  -  initialize a device
//------------------------------------------------------------------------
int
init(int descrp)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return SYSERR;
	devptr = &devtab[descrp];
	(*devptr->dvinit)(devptr);
	return OK;
}
