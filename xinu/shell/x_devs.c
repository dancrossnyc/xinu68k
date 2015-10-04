#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  x_devs  -  (command devs) print main fields of device switch table
//------------------------------------------------------------------------
COMMAND
x_devs(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	const char *hd1 = "Num Device    minor CSR      intvec   cntrl blk\n";
	const char *hd2 = "--- --------  ----- -------- -------- ---------\n";
	struct devsw *devptr;
	char str[60];
	int i;

	write(stdout, hd1, strlen(hd1));
	write(stdout, hd2, strlen(hd2));
	for (i = 0; i < NDEVS; i++) {
		devptr = &devtab[i];
		sprintf(str, "%2d. %-9s %3d   %08x %08x %08x\n",
			i, devptr->name, devptr->minor,
			devptr->csr, devptr->ivec, devptr->iobuf);
		write(stdout, str, strlen(str));
	}

	return OK;
}
