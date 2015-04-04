#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
//  netin - initialize net, start output side, and become input daemon
//   userpid: user process to resume
//------------------------------------------------------------------------
PROCESS
netin(int userpid)
{
	struct epacket *packet;
	int icmpp;

	arpinit();
	netinit();
	icmpp = pcreate(NETFQ);
	resume(create(NETOUT, NETOSTK, NETIPRI - 1, NETONAM,
		      2, userpid, icmpp));

	for (packet = getbuf(Net.netpool); TRUE;) {
		Net.npacket++;
		if (read(ETHER, packet, sizeof(*packet)) == SYSERR) {
			Net.ndrop++;
			continue;
		}
		switch ((int)net2hs(packet->ep_hdr.e_ptype)) {
		case EP_ARP:
			arp_in(packet, ETHER);
			packet = getbuf(Net.netpool);
			break;
		case EP_RARP:
			rarp_in(packet, ETHER);
			packet = getbuf(Net.netpool);
			break;
		case EP_IP:
			ip_in(packet, icmpp, NETFQ);
			packet = getbuf(Net.netpool);
			break;
		default:	// just drop packet
			Net.ndrop++;
		}
	}
}
