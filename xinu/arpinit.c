#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

struct arpblk Arp;

//------------------------------------------------------------------------
//  arpinit  -  initialize data structures for ARP processing
//------------------------------------------------------------------------
void
arpinit(void)
{

	memset(&Arp, 0, sizeof(Arp));
	Arp.atabsiz = 0;
	Arp.atabnxt = 0;
	Arp.arpsem = screate(1);
	Arp.rarpsem = screate(1);
	Arp.arppid = Arp.rarppid = BADPID;
	for (int k = 0; k < AR_TAB; k++) {
		Arp.arptab[k].dev = -1;
	}
}
