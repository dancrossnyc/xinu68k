#include "conf.h"
#include "kernel.h"
#include "q.h"

//------------------------------------------------------------------------
// insert.c  --  insert an process into a q list in key order
//   proc: process to insert
//   head: q index of head of list
//   key: key to use for this process
//------------------------------------------------------------------------
int
insert(int proc, int head, int key)
{
	int next;			// runs through list
	int prev;

	next = q[head].qnext;
	while (q[next].qkey < key)	// tail has MAXINT as key
		next = q[next].qnext;
	q[proc].qnext = next;
	q[proc].qprev = prev = q[next].qprev;
	q[proc].qkey = key;
	q[prev].qnext = proc;
	q[next].qprev = proc;

	return OK;
}
