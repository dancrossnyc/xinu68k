#include "conf.h"
#include "kernel.h"
#include "sleep.h"
#include "network.h"

struct netinfo Net;

//------------------------------------------------------------------------
//  netinit  -  initialize network data structures
//------------------------------------------------------------------------
int
netinit(void)
{

	// Initialize pool of network buffers and rest of Net structure
	if (hasclock == FALSE)
		panic("net: no clock");
	Net.netpool = mkpool(EMAXPAK, NETBUFS);
	for (int i = 0; i < NETQS; i++) {
		struct netq *nqptr = &Net.netqs[i];
		nqptr->valid = FALSE;
		nqptr->uport = -1;
		nqptr->xport = pcreate(NETQLEN);
	}
	Net.mnvalid = Net.mavalid = FALSE;
	dot2ip(Net.gateway, GATEWAY);
	Net.nxtprt = ULPORT;
	Net.nmutex = screate(1);
	Net.npacket = Net.ndrop = Net.nover = 0;

	return OK;
}
