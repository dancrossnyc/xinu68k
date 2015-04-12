#include "conf.h"
#include "kernel.h"
#include "tty.h"
#include "io.h"
#include "slu.h"

//------------------------------------------------------------------------
//  ttyputc - write one character to a tty device
//------------------------------------------------------------------------
int
ttyputc(struct devsw *devptr, int ch)
{
	struct tty *iptr;
	int ps;

	iptr = &tty[devptr->minor];
	if (ch == NEWLINE && iptr->ocrlf)
		ttyputc(devptr, RETURN);
	ps = disable();
	wait(iptr->osem);	// wait for space in queue
	iptr->obuff[iptr->ohead++] = ch;
	if (iptr->ohead >= OBUFLEN)
		iptr->ohead = 0;
	(iptr->ioaddr)->ctstat = SLUENABLE;
	restore(ps);

	return OK;
}
