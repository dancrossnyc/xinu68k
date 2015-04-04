#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  arp_in  -  handle ARP packet coming in from Ethernet network
 *------------------------------------------------------------------------
 */
int
arp_in(struct epacket *packet, int device)
{
	char ps;
	int pid;
	short arop;
	struct arppak *apacptr;
	struct arpent *atabptr;
	struct etblk *etptr;

	etptr = (struct etblk *)devtab[device].dvioblk;
	apacptr = (struct arppak *)packet->ep_data;
	atabptr = &Arp.arptab[arpfind(apacptr->ar_spa)];
	if (atabptr->arp_state != AR_RSLVD) {
		memmove(atabptr->arp_Ead, apacptr->ar_sha, EPADLEN);
		atabptr->arp_dev = device;
		atabptr->arp_state = AR_RSLVD;
	}
	arop = net2hs(apacptr->ar_op);
	switch (arop) {

	case AR_REQ:		// request - answer if for me
		if (memcmp(Net.myaddr, apacptr->ar_tpa, IPLEN) != 0) {
			freebuf(packet);
			return OK;
		}
		apacptr->ar_op = hs2net(AR_RPLY);
		memmove(apacptr->ar_tpa, apacptr->ar_spa, IPLEN);
		memmove(apacptr->ar_tha, packet->ep_hdr.e_src, EPADLEN);
		memmove(packet->ep_hdr.e_dest, apacptr->ar_tha, EPADLEN);
		memmove(apacptr->ar_sha, etptr->etpaddr, EPADLEN);
		memmove(apacptr->ar_spa, Net.myaddr, IPLEN);
		write(device, packet, EMINPAK);
		return OK;

	case AR_RPLY:		// reply - awaken requestor if any
		disable(ps);
		pid = Arp.arppid;
		if (!isbadpid(pid) &&
		    memcmp(Arp.arpwant, apacptr->ar_spa, IPLEN) == 0) {
			Arp.arppid = BADPID;
			send(pid, OK);
		}
		freebuf(packet);
		restore(ps);
		return OK;

	default:
		Net.ndrop++;
		freebuf(packet);
		return SYSERR;
	}
}
