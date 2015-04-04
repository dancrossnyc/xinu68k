#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "ports.h"

//------------------------------------------------------------------------
//  pcreate  --  create a port that allows "count" outstanding messages
//------------------------------------------------------------------------
SYSCALL
pcreate(int count)
{
	char ps;

	if (count < 0)
		return SYSERR;
	disable(ps);
	if (mark(ptmark) == OK)
		pinit(MAXMSGS);
	for (int i = 0; i < NPORTS; i++) {
		struct pt *ptptr;
		int p = ptnextp--;
		if (p <= 0)
			ptnextp = NPORTS - 1;
		ptptr = &ports[p];
		if (ptptr->ptstate != PTFREE) {
			continue;
		}
		ptptr->ptstate = PTALLOC;
		ptptr->ptssem = screate(count);
		ptptr->ptrsem = screate(0);
		ptptr->pthead = ptptr->pttail = (struct ptnode *)NULL;
		ptptr->ptseq++;
		ptptr->ptmaxcnt = count;
		restore(ps);
		return p;
	}
	restore(ps);

	return SYSERR;
}
