#include "conf.h"
#include "kernel.h"
#include "tty.h"
#include "io.h"
#include "slu.h"

INTPROC
ttyint(void *arg)
{
	struct tty *tty = (struct tty *)arg;
	struct csr *csr = tty->ioaddr;
	byte isr = csr->isr;

	if (isr & DUART_TxRDYA) {
		ttyoin(tty);
	}
	if (isr & DUART_RxRDYA) {
		ttyiin(tty);
	}
}
