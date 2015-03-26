// qdump.c - qdump, qdumph, qdumpa

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>

#define	isbadq(i)	((i) < 0 || (i) >= NQENT)

static void
qxdump(int all)
{
	struct qent *qp;
	int i;
	struct pentry *pptr;
	int pr;

	for (i = 0; i < NQENT; i++) {
		qp = NULL;
		if ((pr = all) == 0) {
			qp = &q[i];
			if (i < NPROC) {
				pptr = &proctab[i];
				if (pptr->pstate != PRFREE)
					pr = 1;
			} else {	/* normal queue - could be head or tail */
				if ((qp->qnext < NPROC && qp->qnext >= 0)
				    || (qp->qprev < NPROC
					&& qp->qprev >= 0))
					pr = 1;
				else if (qp->qkey == MAXINT) {
					if (qp->qnext != EMPTY
					    || isbadq(qp->qprev)
					    || q[qp->qprev].qkey != MININT
					    || q[qp->qprev].qnext != i)
						pr = 1;
				} else if (qp->qkey == MININT) {
					if (qp->qprev != EMPTY
					    || isbadq(qp->qnext)
					    || q[qp->qnext].qkey != MAXINT
					    || q[qp->qnext].qprev != i)
						pr = 1;
				} else
					pr = 1;
			}
		}
		if (pr != 0 && qp != NULL)
			kprintf("q[%4d ] key=%6d,next=%6d,qprev=%6d\n",
				i, qp->qkey, qp->qnext, qp->qprev);
	}
}

//------------------------------------------------------------------------
//  qdump  --  dump the contents of the q structure for debugging
//------------------------------------------------------------------------
void
qdump(void)
{
	qxdump(0);
}

//------------------------------------------------------------------------
//  qdumph  --  dump the contents of the q structure and halt
//------------------------------------------------------------------------
void
qdumph(void)
{
	qxdump(0);
	kprintf("\nDump complete -- type P to continue\n");
	halt();
}

//------------------------------------------------------------------------
//  qdumpa  --  dump the contents of the q structure printing all info
//------------------------------------------------------------------------
void
qdumpa(void)
{
	qxdump(1);
}
