#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "bufpool.h"

//------------------------------------------------------------------------
//  freebuf  --  free a buffer that was allocated from a pool by getbuf
//------------------------------------------------------------------------
SYSCALL
freebuf(void *buf)
{
	char ps;
	int poolid;
	int *bp;

#ifdef	MEMMARK
	if (unmarked(bpmark))
		return SYSERR;
#endif
	bp = (int *)buf;
	poolid = *(--bp);
	if (poolid < 0 || poolid >= nbpools)
		return SYSERR;
	disable(ps);
	*bp = (int)bptab[poolid].bpnext;
	bptab[poolid].bpnext = (void *)buf;
	restore(ps);
	signal(bptab[poolid].bpsem);
	return OK;
}
