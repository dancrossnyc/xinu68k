// proc.h - isbadpid

#include "u.h"

// process table declarations and defined constants
#ifndef	NPROC				// set the number of processes
#define	NPROC		10		// allowed if not already done
#endif

// process state constants
enum ProcStates {
	PRCURR = 1,			// process is currently running
	PRFREE,				// process slot is free
	PRREADY,			// process is on ready queue
	PRRECV,				// process waiting for message
	PRSLEEP,			// process is sleeping
	PRSUSP,				// process is suspended
	PRWAIT,				// process is on semaphore queue
	PRTRECV,			// process is timing a receive
};

// miscellaneous process definitions
#define	PNREGS		NREGS		// size of saved register area
#define	PNMLEN		16		// length of process "name"
#define	NULLPROC	0		// id of the null process; it
					// is always eligible to run
#define	BADPID		-1		// used when invalid pid needed

#define	isbadpid(x)	(x<=0 || x>=NPROC)

// process table entry
struct	pentry	{
	int	pstate;			// process state: PRCURR, etc.
	int	pprio;			// process priority
	uword	pregs[PNREGS];		// saved regs. R0-R5,SP,PC,PS
	int	psem;			// semaphore if process waiting
	int	pmsg;			// message sent to this process
	Bool	phasmsg;		// True iff pmsg is valid
	char	*pbase;			// base of run time stack
	short	pstklen;		// stack length
	char	*plimit;		// lowest extent of stack
	char	pname[PNMLEN];		// process name
	int	pargs;			// initial number of arguments
	char	*paddr;			// initial code address
	int	pnxtkin;		// next-of-kin notified of death
	int	pdevs[2];		// devices to close upon exit
};

extern	struct	pentry proctab[];
extern	int	numproc;		// currently active processes
extern	int	nextproc;		// search point for free slot
extern	int	currpid;		// currently executing process
