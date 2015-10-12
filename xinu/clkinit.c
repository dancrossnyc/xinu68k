#include "conf.h"
#include "kernel.h"
#include "sleep.h"

// real-time clock variables and sleeping process queue pointers
volatile int clock6;		// counts in 60ths of a second 6-0
volatile int ticks10;		// counts in 10ths of a second 10-0
volatile int clmutex;		// mutual exclusion for time-of-day
volatile long clktime;		// current time in seconds since 1/1/70
volatile int deferclock;	// non-zero, then deferring clock count
volatile int clkdiff;		// deferred clock ticks
volatile int slnempty;		// FALSE if the sleep queue is empty
volatile int *sltop;		// address of key part of top entry in
				// the sleep queue if slnempty==TRUE
volatile int clockq;		// head of queue of sleeping processes
volatile int preempt;		// preemption counter.  Current process
				// is preempted when it reaches zero;
				// set in resched; counts in ticks
volatile int hasclock;		// set TRUE iff clock exists by setclkr

//------------------------------------------------------------------------
// clkinit - initialize the clock and sleep queue (called at startup)
//------------------------------------------------------------------------
void
clkinit(void)
{
	uword *vector;

	vector = (uword *)CVECTOR;	// set up interrupt vector
	*vector = (uword)clkint;
	setclkr();
	preempt = QUANTUM;	// initial time quantum
	clock6 = 6;		// 60ths of a sec. counter
	ticks10 = 10;		// 10ths of a sec. counter
	clmutex = screate(1);	// semaphore for tod clock
	clktime = 0L;		// initially a low number
	slnempty = FALSE;	// initially, no process asleep
	clkdiff = 0;		// zero deferred ticks
	deferclock = 0;		// clock is not deferred
	clockq = newqueue();	// allocate clock queue in q
	// XXX Hack for simulator.
	extern void mclkstart(void);	// XXX Hack for simulator.
	mclkstart();			// XXX Hack for simulator.
	// XXX Hack for simulator.
}
