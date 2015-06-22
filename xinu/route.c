#include "conf.h"
#include "kernel.h"
#include "network.h"
#include "string.h"

//------------------------------------------------------------------------
//  route  -  route a datagram to a given IP address
//------------------------------------------------------------------------
int
route(IPaddr addr, struct epacket *packet, int totlen)
{
	int result;
	int dev;
	struct arpent *ap;
	IPaddr mynet, destnet;

	// If IP address is broadcast address for my network, then use
	// physical broadcast address.  Otherwise, establish a path to
	// the destination directly or through a gateway
	getnet(mynet);
	netnum(destnet, addr);
	wait(Net.nmutex);

	// NOTE: This code uses host 0 as broadcast like 4.2BSD UNIX.
	if (memcmp(mynet, addr, IPLEN) == 0) {
		dev = ETHER;
		memmove(packet->ep_hdr.e_dest, EBCAST, EPADLEN);
	} else {
		if (memcmp(destnet, mynet, IPLEN) != 0)
			addr = Net.gateway;
		ap = &Arp.arptab[getpath(addr)];
		if (ap->state != ARP_RESOLVED) {
			ap->state = ARP_REMOTE;
			ap = &Arp.arptab[getpath(Net.gateway)];
			if (ap->state != ARP_RESOLVED) {
				panic("route - Cannot reach gateway");
				freebuf(packet);
				signal(Net.nmutex);
				return SYSERR;
			}
		}
		dev = ap->dev;
		memmove(packet->ep_hdr.e_dest, ap->ether_addr, EPADLEN);
	}
	result = write(dev, packet, totlen);
	signal(Net.nmutex);

	return result;
}
