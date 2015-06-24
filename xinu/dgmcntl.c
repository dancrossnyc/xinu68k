#include "conf.h"
#include "kernel.h"
#include "network.h"
#include "string.h"

//------------------------------------------------------------------------
//  dgmcntl  -  control the network and datagram interface pseudo devices
//------------------------------------------------------------------------
int
dgmcntl(struct devsw *devptr, int func, char *addr)
{

	switch (func) {
#ifdef	NETDAEMON
	case NC_SETGW:
		memmove(Net.gateway, addr, IPLEN);
		return OK;
#endif
	default:
		break;
	}

	return SYSERR;
}
