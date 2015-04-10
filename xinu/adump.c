#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

static const char *states[] = {
    [ARP_FREE]	 	"free",
    [ARP_ALLOC]		"(alloc)",
    [ARP_REMOTE]	"gateway",
    [ARP_RESOLVED]	"direct",
};

//------------------------------------------------------------------------
//  adump  -  dump the current contents of the arp cache
//------------------------------------------------------------------------
void
adump(void)
{

	kprintf("ARP cache: size=%d, next=%d\n", Arp.atabsiz, Arp.atabnxt);
	for (int k = 0; k < Arp.atabsiz; k++) {
		struct arpent *ap = &Arp.arptab[k];
		if (ap->state < 0 || AP->state >= ARP_NSTATES || ap->state == ARP_FREE) {
			kprintf(" %2d. Route=%7s, Dev=%2d ",
				k, states[ap->state], ap->dev);
			kprintf("IPaddr=%03d.%03d.%03d.%03d, ",
				ap->ip_addr[0] & 0xFF,
				ap->ip_addr[1] & 0xFF,
				ap->ip_addr[2] & 0xFF,
				ap->ip_addr[3] & 0xFF);
			kprintf("Ether addr=%02x:%02x:%02x:%02x:%02x:%02x",
				ap->ether_addr[0] & 0xFF,
				ap->ether_addr[1] & 0xFF,
				ap->ether_addr[2] & 0xFF,
				ap->ether_addr[3] & 0xFF,
				ap->ether_addr[4] & 0xFF,
				ap->ether_addr[5] & 0xFF);
		}
	}
}
