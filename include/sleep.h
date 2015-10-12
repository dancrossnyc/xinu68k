#define	CVECTOR	0x100			// location of clock interrupt vector

extern volatile int hasclock;		// 1 iff clock exists; 0 otherwise
					// Set at system startup.
extern volatile int clockq;		// q index of sleeping process list
extern volatile int count6;		// used to ignore 5 of 6 interrupts
extern volatile int count10;		// used to ignore 9 of 10 ticks
extern volatile long clktime;		// current time in secs since 1/1/70
extern volatile int clmutex;		// mutual exclusion sem. for clock
extern volatile int *sltop;		// address of first key on clockq
extern volatile int slnempty;		// 1 iff clockq is nonempty

extern volatile int deferclock;		// >0 iff clock interrupts are deferred
extern volatile int clkdiff;		// number of clock ticks deferred
