#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  rfputc  --  put a single character into a remote file
//------------------------------------------------------------------------
int
rfputc(struct devsw *devptr, int ch)
{
	char outch;

	outch = ch;
	if (write(devptr->num, &outch, 1) != 1)
		return SYSERR;

	return OK;
}
