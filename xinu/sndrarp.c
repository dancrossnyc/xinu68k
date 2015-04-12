#include "conf.h"
#include "kernel.h"
#include "network.h"

//------------------------------------------------------------------------
// sndrarp - broadcast a RARP packet to obtain my IP address
//------------------------------------------------------------------------
int
sndrarp(void)
{
	struct epacket *mkarp();
	struct epacket *packet;
	int mypid;
	int resp;
	IPaddr junk;		// needed for argument to mkarp; not ever used
	int ps;

	mypid = getpid();
	for (int k = 0; k < AR_RTRY; k++) {
		packet = mkarp(EP_RARP, AR_RREQ, junk, junk);
		if (packet == (struct epacket *)SYSERR)
			break;
		ps = disable();
		Arp.rarppid = mypid;
		recvclr();
		write(ETHER, packet, EMINPAK);
		resp = recvtim(AR_TIME);
		restore(ps);
		if (resp != TIMEOUT)
			return OK;
	}
	panic("No response to RARP");

	return SYSERR;
}
