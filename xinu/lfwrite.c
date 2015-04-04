#include "conf.h"
#include "kernel.h"

/*------------------------------------------------------------------------
 *  lfwrite  --  write 'count' bytes onto a local disk file
 *------------------------------------------------------------------------
 */
int
lfwrite(struct devsw *devptr, char *buff, int count)
{
	int i;

	if (count < 0)
		return SYSERR;
	for (i = count; i > 0; i--)
		if (lfputc(devptr, *buff++) == SYSERR)
			return SYSERR;
	return count;
}
