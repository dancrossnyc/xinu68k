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
	struct mblock *p, *prev, *leftover;

	ps = disable();
	if (nbytes == 0 || memlist.mnext == NULL) {
		restore(ps);
		return (void *)SYSERR;
	}
	nbytes = (size_t)roundew(nbytes);
	for (prev = &memlist, p = memlist.mnext; p != NULL;
	     prev = p, p = p->mnext) {
		if (p->mlen == nbytes) {
			prev->mnext = p->mnext;
			restore(ps);
			return (void *)p;
		} else if (p->mlen > nbytes) {
			leftover = (struct mblock *)((intptr_t)p + nbytes);
			prev->mnext = leftover;
			leftover->mnext = p->mnext;
			leftover->mlen = p->mlen - nbytes;
			restore(ps);
			return (void *)p;
		}
	}
	restore(ps);

	return (void *)SYSERR;
}
