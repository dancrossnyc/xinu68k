#include "conf.h"
#include "kernel.h"
#include "io.h"
#include "slu.h"
#include "tty.h"
#include "stdarg.h"

#define DELAY	1  //00

//------------------------------------------------------------------------
//  kputc  --  write a character on the console using polled I/O
//
//  c is the character to print from _doprnt
//------------------------------------------------------------------------
static void
kputc(int dev, int c)
{
	volatile struct csr *csrptr;
	struct tty *ttyptr;
	int slowdown;		// added to delay polling, because

	// polling immediately after a
	// transmit seems to cause trouble
	if (c == 0)
		return;
	if (c == NEWLINE)
		kputc(dev, RETURN);
	csrptr = (struct csr *)devtab[dev].csr;			// dev. address
	ttyptr = (struct tty *)devtab[dev].iobuf;		// control block

	if (ttyptr &&
	    (ttyptr->oheld ||
		(ttyptr->oflow &&				// flow control
		 (csrptr->sra & DUART_RxRDYA) &&
		 (csrptr->rbufa & DUART_CHRMASK) == ttyptr->ostop)))
	{
		do {
			while (!(csrptr->sra & DUART_RxRDYA));	// wait for char
		} while ((csrptr->rbufa & DUART_CHRMASK) == ttyptr->ostop);
		ttyptr->oheld = FALSE;
	}

	while (!(csrptr->sra & DUART_TxRDYA));			// poll for idle
	csrptr->tbufa = c;					// transmit char
	for (slowdown = 0; slowdown < DELAY; slowdown++);	// wait a bit
	while (!(csrptr->sra & DUART_TxRDYA));			// poll for idle
}

//------------------------------------------------------------------------
//  savestate  --  save the console control and status register
//------------------------------------------------------------------------
static int
savestate(int dev)
{
	volatile struct csr *c;
	int ps;

	ps = disable();
	c = (struct csr *)devtab[dev].csr;
	c->imr = 0;

	return ps;
}

//------------------------------------------------------------------------
//  restorestate  --  restore the console output control and status register
//------------------------------------------------------------------------
static void
restorestate(int dev, int ps)
{
	volatile struct tty *ttyptr;

	ttyptr = (struct tty *)devtab[dev].iobuf;
	((volatile struct csr *)devtab[dev].csr)->imr = ttyptr->imr;
	restore(ps);
}

//------------------------------------------------------------------------
//  kprintf  --  kernel printf: formatted, unbuffered output to CONSOLE
// Derived by Bob Brown, Purdue U.
// Flow control added by Steve Munson
//------------------------------------------------------------------------
int
kprintf(const char *fmt, ...)
{
	int saveps;
	extern void _doprnt(const char *, va_list, void (*putc)(int, int), int);
	va_list args;
	saveps = savestate(CONSOLE);
	va_start(args, fmt);
	_doprnt(fmt, args, kputc, CONSOLE);
	va_end(args);
	restorestate(CONSOLE, saveps);
	return OK;
}
