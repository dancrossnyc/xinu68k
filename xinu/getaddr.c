// getaddr.c - getaddr

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  getaddr  -  obtain this system's complete address (IP address)
 *------------------------------------------------------------------------
 */
SYSCALL
getaddr(IPaddr address)
{
	wait(Arp.rarpsem);
	if (!Net.mavalid)
		sndrarp();
	signal(Arp.rarpsem);

	if (!Net.mavalid)
		return SYSERR;
	memmove(address, Net.myaddr, IPLEN);
	return OK;
}
