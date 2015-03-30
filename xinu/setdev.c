// setdev.c - setdev

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL
setdev(int pid,			// process to change
       int dev1, int dev2	// device descriptors to set
    )
{
	int *nxtdev;

	if (isbadpid(pid))
		return (SYSERR);
	nxtdev = (int *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;
	return (OK);
}
