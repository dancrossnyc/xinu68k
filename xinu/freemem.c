#include "conf.h"
#include "kernel.h"
#include "mem.h"

//------------------------------------------------------------------------
//  freemem  --  free a memory block, returning it to memlist
//------------------------------------------------------------------------
SYSCALL
freemem(void *b, size_t size)
{
	int ps;
	struct mblock *p, *q, *block = (struct mblock *)b;
	unsigned top;

	if (size == 0 || (u32)block > (u32)maxaddr || ((u32)block) < ((u32)&end))
		return SYSERR;
	size = (u32)roundew(size);
	ps = disable();
	for (p = memlist.mnext, q = &memlist;
	     (char *)p != NULL && p < block;
	     q = p, p = p->mnext);
	if ((top = q->mlen + (u32)q) > (u32)block &&
	    (q != &memlist || (char *)p != NULL) &&
	    (size + (u32)block) > (u32)p) {
		restore(ps);
		return SYSERR;
	}
	if (q != &memlist && top == (u32)block)
		q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ((u32)(q->mlen + (u32)q) == (u32)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);

	return OK;
}
