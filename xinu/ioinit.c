#include "conf.h"
#include "kernel.h"
#include "mc68k/machine.h"
#include "io.h"

//------------------------------------------------------------------------
// iosetvec -- fill in interrupt vectors and dispatch table entries
//------------------------------------------------------------------------
int
iosetvec(int dev, void (*handler)(void), void *arg)
{
	struct devsw *devptr;
	void (**vptr)(void) = (void (**)(void))VECTORS;

	if (isbaddev(dev))
		return SYSERR;
	devptr = &devtab[dev];
	if (devptr->ivec == 0)			// No interrupt support.
		return OK;
	vptr[devptr->ivec] = handler;		// fill in input interrupt
	intrargs[devptr->ivec] = arg;		// fill in handler argument
	return OK;
}
