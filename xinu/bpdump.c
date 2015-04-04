#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <bufpool.h>

//------------------------------------------------------------------------
//  bpdump  -  dump the buffer pool table
//------------------------------------------------------------------------
int
bpdump(void)
{

	for (int i = 0; i < NBPOOLS; i++) {
		struct bpool *bpptr = &bptab[i];
		kprintf("Buffer Pool %2d: buf size=%4d, "
			"sem=%2d, count=%d\n",
			i, bpptr->bpsize, bpptr->bpsem,
			scount(bpptr->bpsem));
	}

	return OK;
}
