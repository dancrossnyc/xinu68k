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
kputc_mduart(int device, int c)
{
#define MDUART_STAT_REG_A	2
#define	MDUART_TXB_REG_A	6
	volatile byte *duart = (byte *)0x100010 + 1;
	while ((duart[MDUART_STAT_REG_A] & 0x04) == 0)
		;
	duart[MDUART_TXB_REG_A] = c;	// transmit char
	if (c == NEWLINE)
		kputc_mduart(device, RETURN);
}

//------------------------------------------------------------------------
//  kputc  --  write a character on the console using polled I/O
//
//  c is the character to print from _doprnt
//------------------------------------------------------------------------
/*
static void
kputc(int device, int c)
{
	struct csr *csrptr;
	struct tty *ttyptr;
	int slowdown;		// added to delay polling, because

	// polling immediately after a
	// transmit seems to cause trouble
	if (c == 0)
		return;
	if (c == NEWLINE)
		kputc(device, RETURN);
	csrptr = (struct csr *)devtab[device].csr;	// dev. address
	ttyptr = (struct tty *)devtab[device].iobuf;	// control block

	if (ttyptr && (ttyptr->oheld || (ttyptr->oflow &&	// flow control
					 (csrptr->crstat & SLUREADY) &&
					 (csrptr->crbuf & SLUCHMASK) ==
					 ttyptr->ostop))) {
		do {
			while (!(csrptr->crstat & SLUREADY));	// wait for char
		} while ((csrptr->crbuf & SLUCHMASK) == ttyptr->ostop);
		ttyptr->oheld = FALSE;
	}

	while (!(csrptr->ctstat & SLUREADY));	// poll for idle
	csrptr->ctbuf = c;	// transmit char
	for (slowdown = 0; slowdown < DELAY; slowdown++);	// wait a bit
	while (!(csrptr->ctstat & SLUREADY));	// poll for idle
}
*/

static int saveps, savedev, savecrstat, savectstat;
//------------------------------------------------------------------------
//  savestate  --  save the console control and status register
//------------------------------------------------------------------------
static void
savestate(int device)
{
	struct csr *c;
	int ps;

	ps = disable();
	saveps = ps;
	savedev = device;
	c = (struct csr *)devtab[device].csr;
	savecrstat = c->crstat & SLUENABLE;
	c->crstat = SLUDISABLE;
	savectstat = c->ctstat & SLUENABLE;
	c->ctstat = SLUDISABLE;
}

//------------------------------------------------------------------------
//  rststate  --  restore the console output control and status register
//------------------------------------------------------------------------
static void
restorestate(void)
{
	int ps;

	((struct csr *)devtab[savedev].csr)->crstat = savecrstat;
	((struct csr *)devtab[savedev].csr)->ctstat = savectstat;
	ps = saveps;
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
	extern void _doprnt(const char *, va_list, void (*putc)(int, int), int);
	va_list args;
	savestate(CONSOLE);
	va_start(args, fmt);
	_doprnt(fmt, args, kputc_mduart, CONSOLE);
	va_end(args);
	restorestate();
	return OK;
}
