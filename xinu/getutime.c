#include "conf.h"
#include "kernel.h"
#include "sleep.h"
#include "date.h"
#include "network.h"

//------------------------------------------------------------------------
// getutime -- obtain time in seconds past Jan 1, 1970, ut (gmt)
//------------------------------------------------------------------------
SYSCALL
getutime(long *timvar)
{
	int dev;
	int ret;
	long utnow;
	char *msg = "No time server response";
return SYSERR;	// XXX hack for simulator.

	wait(clmutex);
	ret = OK;
	if (clktime < SECPERHR) {	// assume small numbers invalid
		if ((dev = open(INTERNET, TSERVER, ANYLPORT)) == SYSERR ||
		    control(dev, DG_SETMODE, DG_TMODE | DG_DMODE) == SYSERR) {
			panic(msg);
			ret = SYSERR;
		}
		write(dev, msg, 2);	// send junk packet to prompt
		if (read(dev, &utnow, 4) != 4) {
			panic(msg);
			ret = SYSERR;
		} else
			clktime = net2xt(net2hl(utnow));
		close(dev);
	}
	*timvar = clktime;
	signal(clmutex);
	return ret;
}
