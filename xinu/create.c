#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "mem.h"
#include "io.h"
#include "stdarg.h"

/*------------------------------------------------------------------------
 * newpid  --  obtain a new (free) process id
 *------------------------------------------------------------------------
 */
static int
newpid(void)
{
	int pid;		// process id to return
	int i;

	for (i = 0; i < NPROC; i++) {	// check all NPROC slots
		if ((pid = nextproc--) <= 0)
			nextproc = NPROC - 1;
		if (proctab[pid].pstate == PRFREE)
			return (pid);
	}
	return (SYSERR);
}

/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *
 *	int	*procaddr;	procedure address
 *	int	ssize;		stack size in words
 *	int	priority;	process priority > 0
 *	char	*name;		name (for debugging)
 *	int	nargs;		number of args that follow
 *	...;			arguments (treated like an array in the code)
 *------------------------------------------------------------------------
 */
SYSCALL
create(PROCESS (*procaddr)(), int ssize, int priority, char *name, int nargs, ...)
{
	va_list args;
	int pid;		// stores new process id
	struct pentry *pptr;	// pointer to proc. table entry
	int i;
	int *saddr;		// stack address
	char ps;		// saved processor status
	uword *procaddrp = (uword *)&procaddr;

	disable(ps);
	ssize = (int)roundew(ssize);
	if (ssize < MINSTK || ((saddr = getstk(ssize)) == (int *)SYSERR) ||
	    (pid = newpid()) == SYSERR || isodd(procaddr) ||
	    priority < 1) {
		restore(ps);
		return (SYSERR);
	}
	numproc++;
	pptr = &proctab[pid];
	pptr->pstate = PRSUSP;
	for (i = 0; i < PNMLEN && (pptr->pname[i] = name[i]) != 0; i++);
	pptr->pprio = priority;
	pptr->pbase = (char *)saddr;
	pptr->pstklen = ssize;
	pptr->psem = 0;
	pptr->phasmsg = FALSE;
	pptr->plimit = (char *)((uword)saddr - ssize + sizeof(int));
	*saddr-- = MAGIC;
	pptr->pargs = nargs;
	for (i = 0; i < PNREGS; i++)
		pptr->pregs[i] = INITREG;
	pptr->paddr = (char *)(*procaddrp);
	pptr->pregs[PC] = *procaddrp;
	pptr->pregs[PS] = INITPS;
	pptr->pnxtkin = BADPID;
	pptr->pdevs[0] = pptr->pdevs[1] = BADDEV;
	va_start(args, nargs);
	saddr -= nargs;
	for (; nargs > 0; nargs--)	// machine dependent; copy args
		*++saddr = va_arg(args, int);	// onto created process's stack
	va_end(args);
	saddr -= nargs;
	*saddr = (int) INITRET;	// push on return address
	pptr->pregs[SP] = (int) saddr;
	restore(ps);

	return (pid);
}
