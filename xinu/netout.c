#include "conf.h"
#include "kernel.h"
#include "network.h"
#include "string.h"

#define  MNAMELEN  24		// maximum size of this machine's name

//------------------------------------------------------------------------
//  netout  -  start network by finding address and forward IP packets
//------------------------------------------------------------------------
PROCESS
netout(int userpid, int icmpp)
{
	struct epacket *packet;
	struct ip *ipptr;
	long tim;
	int len;
	char name[MNAMELEN];
	IPaddr addr;

	getaddr(addr);
	gettime(&tim);
	getname(name, MNAMELEN);
	resume(userpid);
	while (TRUE) {
		packet = (struct epacket *)preceive(icmpp);
		ipptr = (struct ip *)packet->ep_data;
		memmove(addr, ipptr->i_dest, IPLEN);
		len = net2hs(ipptr->i_paclen) - IPHLEN;
		ipsend(addr, packet, len);
	}
}
