#include "conf.h"
#include "kernel.h"
#include "io.h"

/*------------------------------------------------------------------------
 *  write  -  write 1 or more bytes to a device
 *------------------------------------------------------------------------
 */
SYSCALL
write(int descrp, const void *buff, int count)
{
	struct devsw *devptr;

	if (isbaddev(descrp))
		return (SYSERR);
	devptr = &devtab[descrp];

	return (*devptr->dvwrite)(devptr, buff, count);
}
