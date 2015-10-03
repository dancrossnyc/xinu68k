#include "conf.h"
#include "kernel.h"
#include "name.h"

//------------------------------------------------------------------------
//  nameopen  -  open an object (e.g., remote file) based on the name
//------------------------------------------------------------------------
int
nameopen(struct devsw *devptr, char *filename, char *mode)
{
	int dev;
	char newname[NAMLEN];

	dev = namemap(filename, newname);
	if (dev == SYSERR)
		return SYSERR;

	return open(dev, newname, mode);
}
