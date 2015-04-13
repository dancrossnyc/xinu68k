#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  x_close  -  (command close) close a device given its id
//------------------------------------------------------------------------
COMMAND
x_close(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	if (nargs != 2) {
		fprintf(stderr, "use: close device-number\n");
		return SYSERR;
	}
	return close(atoi(args[1]));
}
