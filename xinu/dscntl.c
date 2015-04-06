#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "disk.h"

//------------------------------------------------------------------------
//  dscntl  --  control disk driver/device
//------------------------------------------------------------------------
int
dscntl(struct devsw *devptr, int func)
{
	int stat;
	int ps;

	ps = disable();
	switch (func) {

	case DSKSYNC:
		stat = dsksync(devptr);
		break;

	default:
		stat = SYSERR;
		break;
	}
	restore(ps);
	return stat;
}
