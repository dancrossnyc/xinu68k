#include "conf.h"
#include "kernel.h"
#include "fserver.h"
#include "rfile.h"

struct rfinfo Rf;

//------------------------------------------------------------------------
//  rfinit  --  initialize remote file pseudo devices
//------------------------------------------------------------------------
void
rfinit(struct devsw *devptr)
{
	struct rfblk *rfptr;

	devptr->iobuf = (char *)(rfptr = &Rf.rftab[devptr->minor]);
	rfptr->rf_dnum = devptr->num;
	rfptr->rf_name[0] = NULLCH;
	rfptr->rf_state = RFREE;
	rfptr->rf_mutex = screate(1);
	rfptr->rf_pos = 0L;
	if (devptr->minor == 0) {	// done just once
		Rf.device = RCLOSED;
		Rf.rmutex = screate(1);
	}
}
