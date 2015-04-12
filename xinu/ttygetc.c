#include "conf.h"
#include "kernel.h"
#include "tty.h"
#include "io.h"

//------------------------------------------------------------------------
//  ttygetc - read one character from a tty device
//------------------------------------------------------------------------
int
ttygetc(struct devsw *devptr)
{
	int ps;
	int ch;
	struct tty *iptr;

	ps = disable();
	iptr = &tty[devptr->minor];
	wait(iptr->isem);	// wait for a character in buff
	ch = LOWBYTE & iptr->ibuff[iptr->itail++];
	if (iptr->itail >= IBUFLEN)
		iptr->itail = 0;
	if (iptr->ieof && (iptr->ieofc == ch))
		ch = EOF;
	restore(ps);

	return ch;
}
