extern void ioint();		// interrupt dispatch routine

struct intmap {			// device-to-interrupt routine mapping
	void (*intr)(uword);	// address of interrupt routine
	uword icode;		// argument passed to input routine
};

#ifdef	NDEVS
extern struct intmap intmap[NDEVS];
#define	isbaddev(f)	((f) < 0 || (f) >= NDEVS)
#endif
#define	BADDEV		-1

// In-line I/O procedures
#define	getchar()	getc(CONSOLE)
#define	putchar(ch)	putc(CONSOLE, (ch))
#define	fgetc(unit)	getc((unit))
#define	fputc(unit, ch)	putc((unit), (ch))

// The LSI-11 version of Xinu also saved stored a prototype
// processor status word in the interrupt vector. The 68k
// does not use that; the 68k interrupt vector is just a jump
// table.
struct vector {
	void (*vproc)();	// address of interrupt procedure
};
