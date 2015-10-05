#include "conf.h"
#include "kernel.h"
#include "tty.h"
#include "io.h"
#include "slu.h"

//------------------------------------------------------------------------
// ttyoin -- lower-half tty device driver for output interrupts
//------------------------------------------------------------------------
void
ttyoin(struct tty *iptr)
{
	struct csr *cptr;
	int ct;

	cptr = iptr->ioaddr;
	if (iptr->ehead != iptr->etail) {
		cptr->tbufa = iptr->ebuff[iptr->etail++];
		if (iptr->etail >= EBUFLEN)
			iptr->etail = 0;
		return;
	}
	if (iptr->oheld) {	// honor flow control
		iptr->imr &= ~DUART_TxINTABLE;
		cptr->imr = iptr->imr;
		return;
	}
	if ((ct = scount(iptr->osem)) >= OBUFLEN) {
		iptr->imr &= ~DUART_TxINTABLE;
		cptr->imr = iptr->imr;
		return;
	}
	cptr->tbufa = iptr->obuff[iptr->otail++];
	if (iptr->otail >= OBUFLEN)
		iptr->otail = 0;
	if (ct > OBMINSP)
		signal(iptr->osem);
	else if (++(iptr->odsend) == OBMINSP) {
		iptr->odsend = 0;
		signaln(iptr->osem, OBMINSP);
	}
}
