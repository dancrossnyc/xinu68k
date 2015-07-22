#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"

static const char *regnames[] = {
    "PC",
    "SR",
    "D0",
    "D1",
    "D2",
    "D3",
    "D4",
    "D5",
    "D6",
    "D7",
    "A0",
    "A1",
    "A2",
    "A3",
    "A4",
    "A5",
    "A6",
    "SP",
    "USP",
};

static void
pxdump(int all)
{
	int i, j, ctr;
	int ps;
	struct pentry *pptr;
	ps = disable();
	kprintf("\nProctab at loc %x\ncurrpid is %d\n", proctab, currpid);
	for (i = 0; i < NPROC; i++) {
		pptr = &proctab[i];
		if (all != 0 || pptr->pstate != PRFREE) {
			kprintf("\nProcess %d: ", i);
			kprintf("state=%x,name=", pptr->pstate);
			for (j = 0; j < PNMLEN; j++) {
				if (pptr->pname[j] == '\0')
					break;
				kprintf("%c", pptr->pname[j]);
			}
			kprintf(",prio=%d,sem=%d,stk:base=%x,limit=%x,paddr=%x,",
				pptr->pprio, pptr->psem, pptr->pbase,
				pptr->plimit,pptr->paddr);
			kprintf("MAGIC=%x\n", *((int *)pptr->pbase));
			for (j = 0; j < PNREGS; j++)
				kprintf("(%s)%x ", regnames[j], pptr->pregs[j]);
			kprintf("\n");
		}
	}
	kprintf("rdyhead:");
	ctr = NPROC;
	for (i = q[rdyhead].qnext; i < NPROC; i = q[i].qnext) {
		kprintf("%d ", i);
		if (q[i].qnext == i) {
			kprintf("\nLOOP in ready list");
			break;
		}
		if (--ctr < 0) {
			kprintf("\nCorrupt ready list -- too long");
			break;
		}
	}
	kprintf("\n");
	restore(ps);
}

//------------------------------------------------------------------------
//  prdump  --  dump the active process table entries
//------------------------------------------------------------------------
void
prdump(void)
{
	pxdump(0);
}

//------------------------------------------------------------------------
//  prdumph  --  dump the active process table entries and halt
//------------------------------------------------------------------------
void
prdumph(void)
{
	pxdump(0);
	kprintf("\nDump complete -- type P to continue\n");
	halt();
}

//------------------------------------------------------------------------
//  prdumpa  --  dump the process table entries printing all entries
//------------------------------------------------------------------------
void
prdumpa(void)
{
	pxdump(1);
}
