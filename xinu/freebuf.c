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
	int ps;
	int poolid;
	int *bp;

	if (unmarked(bpmark))
		return SYSERR;
	bp = (int *)buf;
	poolid = *(--bp);
	if (poolid < 0 || poolid >= nbpools)
		return SYSERR;
	ps = disable();
	*bp = (int)bptab[poolid].bpnext;
	bptab[poolid].bpnext = (void *)buf;
	restore(ps);
	signal(bptab[poolid].bpsem);

	return OK;
}
