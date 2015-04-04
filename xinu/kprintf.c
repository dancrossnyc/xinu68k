#include "conf.h"
#include "kernel.h"
#include "io.h"
#include "slu.h"
#include "tty.h"
#include "stdarg.h"

#define DELAY	100
//------------------------------------------------------------------------
//  kputc  --  write a character on the console using polled I/O
//
//  c is the character to print from _doprnt
//------------------------------------------------------------------------
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
	csrptr = (struct csr *)devtab[device].dvcsr;	// dev. address
	ttyptr = (struct tty *)devtab[device].dvioblk;	// control block

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

static int savedev, savecrstat, savectstat;
static char saveps;
//------------------------------------------------------------------------
//  savestate  --  save the console control and status register
//------------------------------------------------------------------------
static void
savestate(int device)
{
	char ps;

	disable(ps);
	saveps = ps;
	savedev = device;
	savecrstat = ((struct csr *)devtab[device].dvcsr)->crstat
	    & SLUENABLE;
	((struct csr *)devtab[device].dvcsr)->crstat = SLUDISABLE;
	savectstat = ((struct csr *)devtab[device].dvcsr)->ctstat
	    & SLUENABLE;
	((struct csr *)devtab[device].dvcsr)->ctstat = SLUDISABLE;
}

//------------------------------------------------------------------------
//  rststate  --  restore the console output control and status register
//------------------------------------------------------------------------
static void
rststate(void)
{
	char ps;

	((struct csr *)devtab[savedev].dvcsr)->crstat = savecrstat;
	((struct csr *)devtab[savedev].dvcsr)->ctstat = savectstat;
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
	_doprnt(fmt, args, kputc, CONSOLE);
	va_end(args);
	rststate();
	return OK;
}
