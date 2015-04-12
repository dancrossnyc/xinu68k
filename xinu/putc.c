#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  putc  -  write a single character to a device
//------------------------------------------------------------------------
SYSCALL
putc(int descrp, int ch)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return SYSERR;
	devptr = &devtab[descrp];

	return (*devptr->putc)(devptr, ch);
}
