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
	struct mblock *p, *prev, *block = (struct mblock *)b;
	intptr_t top;

	if (size == 0 ||
	    (intptr_t)block > (intptr_t)maxaddr ||
	    (intptr_t)block < (intptr_t)&end)
		return SYSERR;
	size = (size_t)roundew(size);
	ps = disable();
	for (p = memlist.mnext, prev = &memlist;
	     p != NULL && p < block;
	     prev = p, p = p->mnext);
	top = prev->mlen + (intptr_t)prev;
	if (top > (intptr_t)block &&
	    (prev != &memlist || p != NULL) &&
	    ((intptr_t)block + size) > (intptr_t)p) {
		restore(ps);
		return SYSERR;
	}
	if (prev != &memlist && top == (intptr_t)block)
		prev->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		prev->mnext = block;
		prev = block;
	}
	if ((prev->mlen + (intptr_t)prev) == (intptr_t)p) {
		prev->mlen += p->mlen;
		prev->mnext = p->mnext;
	}
	restore(ps);

	return OK;
}
