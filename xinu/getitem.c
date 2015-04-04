#include "conf.h"
#include "kernel.h"
#include "q.h"

//------------------------------------------------------------------------
// getfirst  --	 remove and return the first process on a list
//
//   head: q index of head of list
//------------------------------------------------------------------------
int
getfirst(int head)
{
	int proc;		// first process on the list

	proc = q[head].qnext;
	if (proc >= NPROC)
		return EMPTY;

	return dequeue(proc);
}



//------------------------------------------------------------------------
// getlast  --  remove and return the last process from a list
//
//   tail: q index of tail of list
//------------------------------------------------------------------------
int
getlast(int tail)
{
	int proc;		// last process on the list

	proc = q[tail].qprev;
	if (proc >= NPROC)
		return EMPTY;

	return dequeue(proc);
}
