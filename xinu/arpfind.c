#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"
#include "string.h"

//------------------------------------------------------------------------
//  arpfind  -  find or insert entry in ARP cache and return its index
//------------------------------------------------------------------------
int
arpfind(IPaddr addr)
{
	int arindex;
	struct arpent *ap;

	for (int k = 0; k < Arp.atabsiz; k++) {
		ap = &Arp.arptab[k];
		if (memcmp(ap->ip_addr, addr, IPLEN) == 0 &&
		    ap->state != ARP_FREE)
			return k;
	}
	if (Arp.atabsiz < AR_TAB)
		Arp.atabsiz++;
	arindex = Arp.atabnxt++;
	if (Arp.atabnxt >= AR_TAB)
		Arp.atabnxt = 0;
	ap = &Arp.arptab[arindex];
	ap->state = ARP_USED;
	memmove(ap->ip_addr, addr, IPLEN);
	for (int k = 0; k < EPADLEN; k++)
		ap->ether_addr[k] = 0;
	ap->dev = -1;

	return arindex;
}
