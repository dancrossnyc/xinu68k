#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  x_sleep  -  (command sleep) delay for a given number of seconds
//------------------------------------------------------------------------
COMMAND
x_sleep(int stdin, int stdout, int stderr, int nargs, char *args[])
{

	if (nargs != 2) {
		fprintf(stderr, "usage: sleep delay\n");
		return SYSERR;
	}

	return sleep(atoi(args[1]));
}
