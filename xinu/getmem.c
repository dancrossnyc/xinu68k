#include "conf.h"
#include "kernel.h"
#include "mem.h"

//------------------------------------------------------------------------
// getmem  --  allocate heap storage, returning lowest integer address
//------------------------------------------------------------------------
SYSCALL *
getmem(size_t nbytes)
{
	int ps;
	struct mblock *p, *q, *leftover;

	ps = disable();
	if (nbytes == 0 || memlist.mnext == NULL) {
		restore(ps);
		return (void *)SYSERR;
	}
	nbytes = (u32)roundew(nbytes);
	for (q = &memlist, p = memlist.mnext; p != NULL;
	     q = p, p = p->mnext)
		if (p->mlen == nbytes) {
			q->mnext = p->mnext;
			restore(ps);
			return (void *)p;
		} else if (p->mlen > nbytes) {
			leftover = (struct mblock *)((u32)p + nbytes);
			q->mnext = leftover;
			leftover->mnext = p->mnext;
			leftover->mlen = p->mlen - nbytes;
			restore(ps);
			return (void *)p;
		}
	restore(ps);

	return (void *)SYSERR;
}
