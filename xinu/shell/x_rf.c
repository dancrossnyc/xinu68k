#include "conf.h"
#include "kernel.h"
#include "fserver.h"
#include "rfile.h"

//------------------------------------------------------------------------
//  x_rf  -  (command rf) format and print remote file status
//------------------------------------------------------------------------
COMMAND
x_rf(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char str[80];

	sprintf(str, "Remote files: server on dev=%d, server mutex=%d\n",
		Rf.device, Rf.rmutex);
	write(stdout, str, strlen(str));
	for (int i = 0; i < Nrf; i++) {
		struct rfblk *rfptr = &Rf.rftab[i];
		if (rfptr->rf_state == RFREE)
			continue;
		sprintf(str,
			" %2d. name=%-20s, pos=%6D, mode=%03o, sem=%d\n",
			rfptr->rf_dnum, rfptr->rf_name,
			rfptr->rf_pos, rfptr->rf_mode, rfptr->rf_mutex);
		write(stdout, str, strlen(str));
	}

	return OK;
}
