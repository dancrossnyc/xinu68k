/* rarp_in.c - rarp_in */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rarp_in  -  handle RARP packet coming in from Ethernet network
 *------------------------------------------------------------------------
 */
int
rarp_in(struct epacket *packet, int device)
{
	char ps;
	int pid;
	int ret;
	struct arppak *apacptr;
	struct etblk *etptr;

	apacptr = (struct arppak *)packet->ep_data;
	ret = SYSERR;
	if (net2hs(apacptr->ar_op) == AR_RRLY) {
		etptr = (struct etblk *) devtab[device].dvioblk;
		if (memcmp(apacptr->ar_tha, etptr->etpaddr, EPADLEN) == 0) {
			memmove(Net.myaddr, apacptr->ar_tpa, IPLEN);
			netnum(Net.mynet, Net.myaddr);
			disable(ps);
			Net.mavalid = TRUE;
			pid = Arp.rarppid;
			if (!isbadpid(pid)) {
				Arp.rarppid = BADPID;
				send(pid, OK);
			}
			restore(ps);
		}
		ret = OK;
	}
	freebuf(packet);

	return ret;
}
