#include "conf.h"
#include "kernel.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  rfwrite  --  write one or more bytes to a remote file
 *------------------------------------------------------------------------
 */
int
rfwrite(struct devsw *devptr, char *buff, int len)
{

	if (len < 0)
		return SYSERR;
	for (int i = len; i > 0; i -= RDATLEN, buff += RDATLEN)
		if (rfio(devptr, FS_WRITE, buff, min(i, RDATLEN)) == SYSERR)
			return SYSERR;

	return len;
}
