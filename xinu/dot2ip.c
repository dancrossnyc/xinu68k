// dot2ip.c - dot2ip

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  dot2ip  -  convert network address from "decimal dot" form to IPaddr
 *------------------------------------------------------------------------
 */
void
dot2ip(char *ip, int nad1, int nad2, int nad3, int nad4)
{
	*ip++ = LOWBYTE & nad1;
	*ip++ = LOWBYTE & nad2;
	*ip++ = LOWBYTE & nad3;
	*ip++ = LOWBYTE & nad4;
}
