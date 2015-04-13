#include "conf.h"
#include "kernel.h"
#include "file.h"

//------------------------------------------------------------------------
//  x_mv  -  (command mv) move (rename) a file
//------------------------------------------------------------------------
COMMAND
x_mv(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	if (nargs != 3) {
		fprintf(stderr, "usage: mv file tofile\n");
		return SYSERR;
	}
	if (rename(args[1], args[2]) == SYSERR) {
		fprintf(stderr, "Cannot move %s\n", args[1]);
		return SYSERR;
	}
	return OK;
}
