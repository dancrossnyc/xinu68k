#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  control  -  control a device (e.g., set the mode)
//------------------------------------------------------------------------
SYSCALL
control(int descrp, int func, int addr)
{
	struct devsw *dp;

	if (isbaddev(descrp))
		return SYSERR;
	dp = &devtab[descrp];

	return (*dp->ctl)(dp, func, addr, NULL);
}
