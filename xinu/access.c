#include "kernel.h"
#include "conf.h"
#include "file.h"
#include "name.h"

//------------------------------------------------------------------------
//  access  -  determine accessability given file name and desired mode
//------------------------------------------------------------------------
SYSCALL
access(char *name, int mode)
{
	struct devsw *dp;
	int dev;
	char fullname[NAMLEN];

	dev = nammap(name, fullname);
	if (dev == SYSERR)
		return SYSERR;
	dp = &devtab[dev];

	return (*dp->ctl)(dp, FLACCESS, fullname, mode);
}
