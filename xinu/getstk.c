#include "conf.h"
#include "kernel.h"
#include "mem.h"

//------------------------------------------------------------------------
// getstk -- allocate stack memory, returning address of topmost uword
//------------------------------------------------------------------------
SYSCALL *
getstk(size_t nbytes)
{
	struct mblock *p, *prev;	// prev follows p along memlist
	struct mblock *fits, *fitsprev;
	size_t len;
	int ps;

	ps = disable();
	if (nbytes == 0) {
		restore(ps);
		return (void *)SYSERR;
	}
	nbytes = (size_t)roundew(nbytes);
	fits = NULL;
	prev = &memlist;
	for (p = prev->mnext; p != NULL; prev = p, p = p->mnext)
		if (p->mlen >= nbytes) {
			fitsprev = prev;
			fits = p;
		}
	if (fits == NULL) {
		restore(ps);
		return (void *)SYSERR;
	}
	len = fits->mlen;
	if (nbytes == len) {
		fitsprev->mnext = fits->mnext;
	} else {
		fits->mlen -= nbytes;
	}
	fits = (struct mblock *)((intptr_t)fits + len - sizeof(uword));
	restore(ps);

	return (void *)fits;
}
