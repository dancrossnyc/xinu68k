#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "mem.h"
#include "io.h"
#include "stdarg.h"

//------------------------------------------------------------------------
// newpid  --  obtain a new (free) process id
//------------------------------------------------------------------------
static int
newpid(void)
{

	for (int k = 0; k < NPROC; k++) {	// check all NPROC slots
		int pid = nextproc--;		// process id to return
		if (pid <= 0)
			nextproc = NPROC - 1;
		if (proctab[pid].pstate == PRFREE)
			return pid;
	}

	return SYSERR;
}

//------------------------------------------------------------------------
//  create  -  create a process to start running a procedure
//
//	int	*procaddr;	procedure address
//	int	ssize;		stack size in words
//	int	priority;	process priority > 0
//	char	*name;		name (for debugging)
//	int	nargs;		number of args that follow
//	...;			arguments (treated like an array in the code)
//------------------------------------------------------------------------
SYSCALL
create(PROCESS (*procaddr)(), int ssize, int priority, char *name, int nargs, ...)
{
	va_list args;
	int pid;		// stores new process id
	struct pentry *pptr;	// pointer to proc. table entry
	int i;
	uword *saddr;		// stack address
	uintptr_t *procaddrp = (uintptr_t *)&procaddr;
	int ps;			// saved processor status

	ps = disable();
	ssize = (int)roundew(ssize);
	if (ssize < MINSTK ||
	    ((saddr = (uword *)getstk(ssize)) == (uword *)SYSERR) ||
	    (pid = newpid()) == SYSERR ||
	    isodd(procaddr) ||
	    priority < 1) {
		restore(ps);
		return SYSERR;
	}
	numproc++;
	pptr = &proctab[pid];
	pptr->pstate = PRSUSP;
	strncpy(pptr->pname, name, PNMLEN);
	pptr->pprio = priority;
	pptr->pbase = (char *)saddr;
	pptr->pstklen = ssize;
	pptr->psem = 0;
	pptr->phasmsg = FALSE;
	pptr->plimit = (char *)((uintptr_t)saddr - ssize + sizeof(uword));
	*saddr-- = MAGIC;
	pptr->pargs = nargs;
	for (i = 0; i < PNREGS; i++)
		pptr->pregs[i] = INITREG;
	pptr->paddr = (void *)(*procaddrp);
	pptr->pregs[PC] = *procaddrp;
	pptr->pregs[SR] = INITSR;
	pptr->pnxtkin = BADPID;
	pptr->pdevs[0] = pptr->pdevs[1] = BADDEV;
	va_start(args, nargs);
	for (; nargs > 0; nargs--)		// machine dependent; copy args
		*saddr-- = va_arg(args, uword);	// onto created process's stack
	va_end(args);
	saddr -= nargs;
	*saddr = (uintptr_t)INITRET;		// push on return address
	pptr->pregs[SP] = (uintptr_t)saddr;
	restore(ps);

	return pid;
}
