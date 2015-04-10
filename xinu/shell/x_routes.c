// x_routes.c - x_routes

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

static char st[] = "F?GD";

//------------------------------------------------------------------------
//  x_routes  -  (command routes) format and print routing cache entries
//------------------------------------------------------------------------
COMMAND
x_routes(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char str[80];

	if (nargs > 1) {
		Arp.atabsiz = Arp.atabnxt = 0;
		return(OK);
	}
	sprintf(str, "Routing cache: size=%d, next=%d\n",
		Arp.atabsiz, Arp.atabnxt);
	write(stdout, str, strlen(str));
	for (int k = 0; k < Arp.atabsiz; k++) {
		struct arpent *ap = &Arp.arptab[k];
		if (ap->state < 0 || ap->state >= sizeof(st) || ap->state == ARP_FREE)
			continue;
		sprintf(str, " %2d. Route=%c, Dev=%2d",
			k, st[ap->state], ap->dev);
		sprintf(&str[strlen(str)], " IPaddr=%03d.%03d.%03d.%03d, ",
			ap->ip_addr[0] & 0xFF,
			ap->ip_addr[1] & 0xFF,
			ap->ip_addr[2] & 0xFF,
			ap->ip_addr[3] & 0xFF);
		sprintf(&str[strlen(str)], "Ether addr=%02x:%02x:%02x:%02x:%02x:%02x\n",
			ap->ether_addr[0] & 0xFF,
			ap->ether_addr[1] & 0xFF,
			ap->ether_addr[2] & 0xFF,
			ap->ether_addr[3] & 0xFF,
			ap->ether_addr[4] & 0xFF,
			ap->ether_addr[5] & 0xFF );
		write(stdout, str, strlen(str));
	}

	return OK;
}
