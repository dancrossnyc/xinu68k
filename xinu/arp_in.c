#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
//  arp_in  -  handle ARP packet coming in from Ethernet network
//------------------------------------------------------------------------
int
arp_in(struct epacket *packet, int device)
{
	int pid;
	uint16 arop;
	struct arppak *arp_packet;
	struct arpent *ap;

	arp_packet = (struct arppak *)packet->ep_data;
	ap = &Arp.arptab[arpfind(arp_packet->ar_spa)];
	if (ap->state != ARP_RESOLVED) {
		memmove(ap->ether_addr, arp_packet->ar_sha, EPADLEN);
		ap->dev = device;
		ap->state = ARP_RESOLVED;
	}
	arop = net2hs(arp_packet->ar_op);
	switch (arop) {
	case AR_REQUEST: {		// request - answer if for me
		struct etblk *ether_frame = (struct etblk *)devtab[device].iobuf;
		if (memcmp(Net.myaddr, arp_packet->ar_tpa, IPLEN) != 0) {
			freebuf(packet);
			return OK;
		}
		arp_packet->ar_op = hs2net(AR_RPLY);
		memmove(arp_packet->ar_tpa, arp_packet->ar_spa, IPLEN);
		memmove(arp_packet->ar_tha, packet->ep_hdr.e_src, EPADLEN);
		memmove(packet->ep_hdr.e_dest, arp_packet->ar_tha, EPADLEN);
		memmove(arp_packet->ar_sha, ether_frame->etpaddr, EPADLEN);
		memmove(arp_packet->ar_spa, Net.myaddr, IPLEN);
		write(device, packet, EMINPAK);
		return OK;
	}
	case AR_RPLY: {		// reply - awaken requestor if any
		int ps = disable();
		pid = Arp.arppid;
		if (!isbadpid(pid) &&
		    memcmp(Arp.arpwant, arp_packet->ar_spa, IPLEN) == 0) {
			Arp.arppid = BADPID;
			send(pid, OK);
		}
		freebuf(packet);
		restore(ps);
		return OK;
	}
	default:
		Net.ndrop++;
		freebuf(packet);
		return SYSERR;
	}
}
