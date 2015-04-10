#include "conf.h"
#include "kernel.h"
#include "file.h"
#include "name.h"

//------------------------------------------------------------------------
//  rename  -  rename a file (key is optional)
//------------------------------------------------------------------------
SYSCALL
rename(char *old, char *new)
{
	struct devsw *dp;
	int dev, dev2;
	char fullold[NAMLEN];
	char fullnew[NAMLEN];

	// map names through namespace and restrict to single device
	if ((dev = nammap(old, fullold)) == SYSERR ||
	    (dev2 = nammap(new, fullnew)) == SYSERR ||
	    dev != dev2)
		return SYSERR;
	dp = &devtab[dev];

	return (*dp->ctl)(dp, FLRENAME, fullold, fullnew);
}
