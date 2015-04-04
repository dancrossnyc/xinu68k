#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
//  mkarp  -  allocate and fill in an ARP or RARP packet
//------------------------------------------------------------------------
struct epacket *
mkarp(int typ, int op, IPaddr spaddr, IPaddr tpaddr)
{
	struct arppak *apacptr;
	struct epacket *packet;

	packet = (struct epacket *) getbuf(Net.netpool);
	if (((int) packet) == SYSERR)
		return (struct epacket *)SYSERR;
	memmove(packet->ep_hdr.e_dest, EBCAST, AR_HLEN);
	packet->ep_hdr.e_ptype = hs2net(typ);
	apacptr = (struct arppak *) packet->ep_data;
	apacptr->ar_hrd = hs2net(AR_HRD);
	apacptr->ar_prot = hs2net(AR_PROT);
	apacptr->ar_hlen = AR_HLEN;
	apacptr->ar_plen = AR_PLEN;
	apacptr->ar_op = hs2net(op);
	memmove(apacptr->ar_sha, eth[0].etpaddr, AR_HLEN);
	memmove(apacptr->ar_spa, spaddr, AR_PLEN);
	memmove(apacptr->ar_tha, eth[0].etpaddr, AR_HLEN);
	memmove(apacptr->ar_tpa, tpaddr, AR_PLEN);

	return packet;
}
