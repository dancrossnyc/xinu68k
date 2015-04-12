#include "conf.h"
#include "kernel.h"
#include "file.h"
#include "name.h"

//------------------------------------------------------------------------
//  remove  -  remove a file given its name (key is optional)
//------------------------------------------------------------------------
SYSCALL
remove(char *name, int key)
{
	struct devsw *dp;
	int dev;
	char fullname[NAMLEN];

	dev = namemap(name, fullname);
	if (dev == SYSERR)
		return SYSERR;
	dp = &devtab[dev];

	return (*dp->ctl)(dp, FLREMOVE, fullname, key);
}
