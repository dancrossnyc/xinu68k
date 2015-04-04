#include "conf.h"
#include "kernel.h"
#include "proc.h"

/*------------------------------------------------------------------------
 * setdev  -  set the two device entries in the process table entry
 *
 *   pid: process to change
 *   dev1, dev2: device descriptors to set
 *------------------------------------------------------------------------
 */
SYSCALL
setdev(int pid, int dev1, int dev2)
{
	int *nxtdev;

	if (isbadpid(pid))
		return SYSERR;
	nxtdev = (int *)proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

	return OK;
}
