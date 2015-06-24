#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "proc.h"

static char hd1[] = "pid   name   state prio  stack range  stack length sem message\n";
static char hd2[] = "--- -------- ----- ---- ------------- ------------ --- -------\n";
static char *pstnams[] = {
	"curr ", "free ", "ready", "recv ",
	"sleep", "susp ", "wait ", "rtim "
};

static int psavsp;

//------------------------------------------------------------------------
//  x_ps  -  (command ps) format and print process table information
//------------------------------------------------------------------------
COMMAND
x_ps(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char str[80];
	uintptr_t currstk;

	//asm("mov sp,_psavsp");        // capture current stack pointer
	proctab[currpid].pregs[SP] = psavsp;
	write(stdout, hd1, strlen(hd1));
	write(stdout, hd2, strlen(hd2));
	for (int k = 0; k < NPROC; k++) {
		struct pentry *pptr = &proctab[k];
		if (pptr->pstate == PRFREE)
			continue;
		sprintf(str, "%3d %8s %s ", k, pptr->pname,
			pstnams[pptr->pstate - 1]);
		write(stdout, str, strlen(str));
		sprintf(str, "%4d %08x-%08x ", pptr->pprio, pptr->plimit,
			(uintptr_t)pptr->pbase + 1);
		write(stdout, str, strlen(str));
		currstk = pptr->pregs[SP];
		if ((char *)currstk < pptr->plimit ||
		    (char *)currstk > pptr->pbase)
			sprintf(str, " OVERFLOWED)");
		else
			sprintf(str, "%4d /%4d    ", pptr->pbase - currstk,
				pptr->pbase - pptr->plimit + sizeof(int));
		write(stdout, str, strlen(str));
		if (pptr->pstate == PRWAIT)
			sprintf(str, "%2d", pptr->psem);
		else
			sprintf(str, "- ");
		write(stdout, str, strlen(str));
		if (pptr->phasmsg)
			sprintf(str, "%06o\n", pptr->pmsg);
		else
			sprintf(str, "   -\n");
		write(stdout, str, strlen(str));
	}

	return OK;
}
