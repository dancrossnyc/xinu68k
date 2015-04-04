#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
//  nqalloc  -  allocate a network demultiplexing queue
//------------------------------------------------------------------------
int
nqalloc(void)
{
	char ps;

	disable(ps);
	for (int i = 0; i < NETQS; i++) {
		struct netq *nqptr = &Net.netqs[i];
		if (!nqptr->valid) {
			nqptr->valid = TRUE;
			nqptr->uport = -1;
			nqptr->pid = BADPID;
			restore(ps);
			return i;
		}
	}
	restore(ps);

	return SYSERR;
}
