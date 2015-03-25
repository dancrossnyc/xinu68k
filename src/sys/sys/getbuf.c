/* getbuf.c - getbuf */

#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <bufpool.h>

/*------------------------------------------------------------------------
 *  getbuf  --  get a buffer from a preestablished buffer pool
 *------------------------------------------------------------------------
 */
void *
getbuf(int poolid)
{
	char ps;
	int *buf;

#ifdef	MEMMARK
	if (unmarked(bpmark))
		return (void *)SYSERR;
#endif
	if (poolid < 0 || poolid >= nbpools)
		return (void *)SYSERR;
	wait(bptab[poolid].bpsem);
	disable(ps);
	buf = (int *)bptab[poolid].bpnext;
	bptab[poolid].bpnext = (char *)(*buf);
	restore(ps);
	*buf++ = poolid;
	return (void *)buf;
}
