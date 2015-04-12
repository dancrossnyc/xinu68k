#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  read  -  read one or more bytes from a device
//------------------------------------------------------------------------
SYSCALL
read(int descrp, void *buff, int count)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return SYSERR;
	devptr = &devtab[descrp];

	return (*devptr->read)(devptr, buff, count);
}
