#include "conf.h"
#include "kernel.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  dgmcntl  -  control the network and datagram interface pseudo devices
 *------------------------------------------------------------------------
 */
int
dgmcntl(struct devsw *devptr, int func, char *addr)
{
	int status;

	switch (func) {
#ifdef	NETDAEMON
	case NC_SETGW:
		memmove(Net.gateway, addr, IPLEN);
		status = OK;
		break;
#endif
	default:
		status = SYSERR;
	}
	return status;
}
