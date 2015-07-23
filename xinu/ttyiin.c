#include "conf.h"
#include "kernel.h"
#include "tty.h"
#include "io.h"
#include "slu.h"

//------------------------------------------------------------------------
//  eputc - put one character in the echo queue
//------------------------------------------------------------------------
static void
eputc(int ch, struct tty *iptr, struct csr *cptr)
{
	iptr->ebuff[iptr->ehead++] = ch;
	if (iptr->ehead >= EBUFLEN)
		iptr->ehead = 0;
	//cptr->ctstat = SLUENABLE;
}

//------------------------------------------------------------------------
//  erase1  --  erase one character honoring erasing backspace
//------------------------------------------------------------------------
static void
erase1(struct tty *iptr, struct csr *cptr)
{
	char ch;

	if (--(iptr->ihead) < 0)
		iptr->ihead += IBUFLEN;
	ch = iptr->ibuff[iptr->ihead];
	if (iptr->iecho) {
		if (ch < BLANK || ch == DEL) {
			if (iptr->evis) {
				eputc(BACKSP, iptr, cptr);
				if (iptr->ieback) {
					eputc(BLANK, iptr, cptr);
					eputc(BACKSP, iptr, cptr);
				}
			}
			eputc(BACKSP, iptr, cptr);
			if (iptr->ieback) {
				eputc(BLANK, iptr, cptr);
				eputc(BACKSP, iptr, cptr);
			}
		} else {
			eputc(BACKSP, iptr, cptr);
			if (iptr->ieback) {
				eputc(BLANK, iptr, cptr);
				eputc(BACKSP, iptr, cptr);
			}
		}
	} else
		return; //cptr->ctstat = SLUENABLE;
}

//------------------------------------------------------------------------
// echoch  --  echo a character with visual and ocrlf options
// ch is character to echo
// iptr is pointer to I/O block for this devptr
// cptr	is csr address for this devptr
//------------------------------------------------------------------------
static void
echoch(int ch, struct tty *iptr, struct csr *cptr)
{
	if ((ch == NEWLINE || ch == RETURN) && iptr->ecrlf) {
		eputc(RETURN, iptr, cptr);
		eputc(NEWLINE, iptr, cptr);
	} else if ((ch < BLANK || ch == DEL) && iptr->evis) {
		eputc(UPARROW, iptr, cptr);
		eputc(ch + 0x40, iptr, cptr);	// make it printable
	} else {
		eputc(ch, iptr, cptr);
	}
}

//------------------------------------------------------------------------
//  ttyiin  --  lower-half tty device driver for input interrupts
//  iptr is pointer to tty block
//------------------------------------------------------------------------
INTPROC
ttyiin(struct tty *iptr)
{
	struct csr *cptr;
	int ch;
	int ct;

	cptr = iptr->ioaddr;
	if ((ch = cptr->crbuf) & SLUERMASK)	// read char from device
		return;		// discard if error
	if (iptr->imode == IMRAW) {
		if (scount(iptr->isem) >= IBUFLEN) {
			return;	// discard if no space
		}
		iptr->ibuff[iptr->ihead++] = ch & SLUCHMASK;
		if (iptr->ihead >= IBUFLEN)	// wrap buffer pointer
			iptr->ihead = 0;
		signal(iptr->isem);
	} else {		// cbreak | cooked mode
		ch &= SLUCHMASK;
		if (ch == RETURN && iptr->icrlf)
			ch = NEWLINE;
		if (iptr->iintr && ch == iptr->iintrc) {
			send(iptr->iintpid, INTRMSG);
			eputc(ch, iptr, cptr);
			return;
		}
		if (iptr->oflow) {
			if (ch == iptr->ostart) {
				iptr->oheld = FALSE;
				//cptr->ctstat = SLUENABLE;
				return;
			}
			if (ch == iptr->ostop) {
				iptr->oheld = TRUE;
				return;
			}
		}
		iptr->oheld = FALSE;
		if (iptr->imode == IMCBREAK) {	// cbreak mode
			if (scount(iptr->isem) >= IBUFLEN) {
				eputc(iptr->ifullc, iptr, cptr);
				return;
			}
			iptr->ibuff[iptr->ihead++] = ch;
			if (iptr->ihead >= IBUFLEN)
				iptr->ihead = 0;
			if (iptr->iecho)
				echoch(ch, iptr, cptr);
			if (scount(iptr->isem) < IBUFLEN)
				signal(iptr->isem);
		} else {	// cooked mode
			if (ch == iptr->ikillc && iptr->ikill) {
				iptr->ihead -= iptr->icursor;
				if (iptr->ihead < 0)
					iptr->ihead += IBUFLEN;
				iptr->icursor = 0;
				eputc(RETURN, iptr, cptr);
				eputc(NEWLINE, iptr, cptr);
				return;
			}
			if (ch == iptr->ierasec && iptr->ierase) {
				if (iptr->icursor > 0) {
					iptr->icursor--;
					erase1(iptr, cptr);
				}
				return;
			}
			if (ch == NEWLINE || ch == RETURN ||
			    (iptr->ieof && ch == iptr->ieofc)) {
				if (iptr->iecho) {
					echoch(ch, iptr, cptr);
					if (ch == iptr->ieofc)
						echoch(NEWLINE, iptr, cptr);
				}
				iptr->ibuff[iptr->ihead++] = ch;
				if (iptr->ihead >= IBUFLEN)
					iptr->ihead = 0;
				ct = iptr->icursor + 1;	// +1 for \n or \r
				iptr->icursor = 0;
				signaln(iptr->isem, ct);
				return;
			}
			ct = scount(iptr->isem);
			ct = ct < 0 ? 0 : ct;
			if ((ct + iptr->icursor) >= IBUFLEN - 1) {
				eputc(iptr->ifullc, iptr, cptr);
				return;
			}
			if (iptr->iecho)
				echoch(ch, iptr, cptr);
			iptr->icursor++;
			iptr->ibuff[iptr->ihead++] = ch;
			if (iptr->ihead >= IBUFLEN)
				iptr->ihead = 0;
		}
	}
}
