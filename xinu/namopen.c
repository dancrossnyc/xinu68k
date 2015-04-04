#include "conf.h"
#include "kernel.h"
#include "name.h"

//------------------------------------------------------------------------
//  namopen  -  open an object (e.g., remote file) based on the name
//------------------------------------------------------------------------
int
namopen(struct devsw *devptr, char *filenam, char *mode)
{
	int dev;
	char newname[NAMLEN];

	dev = nammap(filenam, newname);
	if (dev == SYSERR)
		return SYSERR;

	return open(dev, newname, mode);
}
