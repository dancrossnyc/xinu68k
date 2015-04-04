#include "conf.h"
#include "kernel.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  rfgetc  --  get a character from a remote file
 *------------------------------------------------------------------------
 */
int
rfgetc(struct devsw *devptr)
{
	char ch;
	int retcode;

	if ((retcode = read(devptr->dvnum, &ch, 1)) == 1)
		return ch;
	if (retcode == 0)
		return EOF;

	return SYSERR;
}
