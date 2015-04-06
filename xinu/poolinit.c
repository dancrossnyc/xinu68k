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
	int ps;

	ps = disable();
	status = mark(bpmark);
	if (status == OK) {
		nbpools = 0;
	}
	restore(ps);

	return (status == OK) ? OK : SYSERR;
}
