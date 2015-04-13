#include "conf.h"
#include "kernel.h"
#include "file.h"

//------------------------------------------------------------------------
//  x_rm  -  (command rm) remove a file given its name
//------------------------------------------------------------------------
COMMAND
x_rm(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	if (nargs != 2) {
		fprintf(stderr, "usage: rm file\n");
		return SYSERR;
	}
	if (remove(args[1], 0) == SYSERR) {
		fprintf(stderr, "Cannot remove %s\n", args[1]);
		return SYSERR;
	}
	return OK;
}
