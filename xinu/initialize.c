#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "sem.h"
#include "sleep.h"
#include "mem.h"
#include "tty.h"
#include "q.h"
#include "io.h"
#include "disk.h"
#include "network.h"

// Declarations of major kernel variables
struct pentry proctab[NPROC];	// process table
int nextproc;			// next process slot to use in create
struct sentry semaph[NSEM];	// semaphore table
int nextsem;			// next semaphore slot to use in screate
struct qent q[NQENT];		// q table (see queue.c)
int nextqueue;			// next slot in q structure to use
char *maxaddr;			// max memory address (set by sizmem)
struct intmap intmap[NDEVS];	// interrupt dispatch table
struct mblock memlist;		// list of free memory blocks
struct tty tty[Ntty];		// SLU buffers and mode control

// active system status
int numproc;			// number of live user processes
int currpid;			// id of currently running process
int reboot = 0;			// non-zero after first boot

int rdyhead, rdytail;		// head/tail of ready list (q indexes)
char vers[] = VERSION;		// Xinu version printed at startup

//**********************************************************************
//**				NOTE:				      **
//**								      **
//**   This is where the system begins after the C environment has    **
//**   been established.  Interrupts are initially DISABLED, and      **
//**   must eventually be enabled explicitly.  This routine turns     **
//**   itself into the null process after initialization.  Because    **
//**   the null process must always remain ready to run, it cannot    **
//**   execute code that might cause it to be suspended, wait for a   **
//**   semaphore, or put to sleep, or exit.  In particular, it must   **
//**   not do I/O unless it uses kprintf for polled output.           **
//**								      **
//**********************************************************************

static void
init_mduart()
{
#define	MDUART_STAT_REG_A	2
#define	MDUART_CTL_REG_A	4
#define	MDUART_MR1_REG_A	0
#define	MDUART_MR2_REG_A	0

	volatile byte *duart = (byte *)0x100010 + 1;
	duart[MDUART_CTL_REG_A] = 0x10;		// Reset MR?A pointer
	duart[MDUART_MR1_REG_A] = 0x23;		// 8 data bits
	duart[MDUART_MR2_REG_A] = 0x17;		// Normal mode
	duart[MDUART_STAT_REG_A] = 0xBB;	// Set clock to 9600
	duart[MDUART_CTL_REG_A] = 0x05;		// Enable Rx and Tx
}

//------------------------------------------------------------------------
//  sysinit  --  initialize all Xinu data structures and devices
//------------------------------------------------------------------------
static int
sysinit(void)
{
	static int (*nulluserp)() = &nulluser;
	static uword *nulluserpp = (uword *)&nulluserp;

	struct pentry *pptr;
	struct mblock *mptr;

	// initialize system variables
	numproc = 0;
	nextproc = NPROC - 1;
	nextsem = NSEM - 1;
	nextqueue = NPROC;	// q[0..NPROC-1] are processes

	// initialize free memory list
	memlist.mnext = mptr = (struct mblock *)roundew(&end);
	mptr->mnext = (struct mblock *)NULL;
	mptr->mlen = (uword)truncew((uintptr_t)maxaddr - NULLSTK - (uintptr_t)&end);

	// initialize process table
	for (int k = 0; k < NPROC; k++)
		proctab[k].pstate = PRFREE;

	// initialize null process entry
	pptr = &proctab[NULLPROC];
	pptr->pstate = PRCURR;
	pptr->pprio = 0;
	strcpy(pptr->pname, "prnull");
	pptr->plimit = ((char *)maxaddr) - NULLSTK - sizeof(uword);
	pptr->pbase = (char *)maxaddr;
	*((uword *)pptr->pbase) = MAGIC;
	pptr->paddr = (char *)(*nulluserpp);
	pptr->phasmsg = FALSE;
	pptr->pargs = 0;
	currpid = NULLPROC;

	// initialize semaphores
	for (int k = 0; k < NSEM; k++) {
		struct sentry *sptr = &semaph[k];
		sptr->sstate = SFREE;
		sptr->sqtail = 1 + (sptr->sqhead = newqueue());
	}

	// initialize ready list
	rdytail = 1 + (rdyhead = newqueue());

	// initialize memory marking
	_mkinit();

	// initialize r.t.clock
	clkinit();

	// initialize disk buffers
	dskdbp = mkpool(DBUFSIZ, NDBUFF);
	dskrbp = mkpool(DREQSIZ, NDREQ);

	// initialize devices
	for (int k = 0; k < NDEVS; k++)
		init(k);

	return OK;
}

//------------------------------------------------------------------------
//  nulluser  -- initialize system and become the null process (id==0)
//------------------------------------------------------------------------
int
nulluser(void)
{				// babysit CPU when no one home
	int userpid;

	init_mduart();		// XXX Hack for simulator.

	kprintf("\n\nXinu Version %s", vers);
	if (reboot++ > 0)
		kprintf("   (reboot %d)", reboot);
	kprintf("\n");

	// initialize all of Xinu
	sysinit();

	kprintf("%lu real mem\n", (uintptr_t)maxaddr + sizeof(int));
	kprintf("%lu avail mem\n", (uintptr_t)maxaddr - (uintptr_t)&end + sizeof(int));
	kprintf("clock %sabled\n\n", hasclock ? "en" : "dis");

	// enable interrupts
	enable();

	// create a process to execute the user's main program
	userpid = create(main, INITSTK, INITPRIO, INITNAME, INITARGS);

#ifdef	NETDAEMON
	// start the network input daemon process
	resume(create(NETIN, NETISTK, NETIPRI, NETINAM, NETIARGC, userpid));
#else
	resume(userpid);
#endif

	for (;;) {		// run forever without actually
		pause();	// executing instructions
	}

	return SYSERR;
}
