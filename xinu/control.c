#include "conf.h"
#include "kernel.h"
#include "io.h"

/*------------------------------------------------------------------------
 *  control  -  control a device (e.g., set the mode)
 *------------------------------------------------------------------------
 */
SYSCALL
control(int descrp, int func, int addr)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return (SYSERR);
	devptr = &devtab[descrp];
	return (*devptr->dvcntl)(devptr, func, addr, NULL);
}
