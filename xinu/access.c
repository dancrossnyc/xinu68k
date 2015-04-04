#include <kernel.h>
#include <conf.h>
#include <file.h>
#include <name.h>

//------------------------------------------------------------------------
//  access  -  determine accessability given file name and desired mode
//------------------------------------------------------------------------
SYSCALL
access(char *name, int mode)
{
	char fullnam[NAMLEN];
	struct devsw *devptr;
	int dev;

	if ((dev = nammap(name, fullnam)) == SYSERR)
		return SYSERR;
	devptr = &devtab[dev];
	return (*devptr->dvcntl)(devptr, FLACCESS, fullnam, mode);
}
