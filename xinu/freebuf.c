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
	int pool;
	int *bp;

	if (unmarked(bpmark))
		return SYSERR;
	bp = (int *)buf;
	pool = *(--bp);
	if (pool < 0 || pool >= nbpools)
		return SYSERR;
	ps = disable();
	*bp = (int)bptab[pool].bpnext;
	bptab[pool].bpnext = (void *)buf;
	restore(ps);
	signal(bptab[pool].bpsem);

	return OK;
}
