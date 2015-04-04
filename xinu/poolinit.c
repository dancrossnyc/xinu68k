#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "bufpool.h"

struct bpool bptab[NBPOOLS];
size_t nbpools;
MARKER bpmark;			// self initializing mark

//------------------------------------------------------------------------
//  poolinit  --  initialize the buffer pool routines
//------------------------------------------------------------------------
int
poolinit(void)
{
	int status;
	char ps;

	disable(ps);
	if ((status = mark(bpmark)) == OK) {
		nbpools = 0;
	}
	restore(ps);

	return (status == OK) ? OK : SYSERR;
}
