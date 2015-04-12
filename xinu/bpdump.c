#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "bufpool.h"

//------------------------------------------------------------------------
//  bpdump  -  dump the buffer pool table
//------------------------------------------------------------------------
int
bpdump(void)
{

	for (int k = 0; k < NBPOOLS; k++) {
		struct bpool *bp = &bptab[k];
		kprintf("Buffer Pool %2d: buf size=%4d, "
			"sem=%2d, count=%d\n",
			k, bp->bpsize, bp->bpsem,
			scount(bp->bpsem));
	}

	return OK;
}
