/* fsndrply.c - fsndrply */

#include "fs.h"

//------------------------------------------------------------------------
// fsndrply  -  send a reply packet to a  specified foreign address
//   s: socket on which to write
//   fptr: data to write
//   len: length of data to write
//   toaddr: send to this Internet address
//   tolen: length of address field
//------------------------------------------------------------------------
int
fsndrply(int s, struct fpacket *fptr, int len, struct sockaddr *toaddr, int tolen)
{
	// Convert inetgers from host byte order to network byte order
	fptr->fp_h.f_op = htons(fptr->fp_h.f_op);
	fptr->fp_h.f_pos = htonl(fptr->fp_h.f_pos);
	fptr->fp_h.f_count = htons(fptr->fp_h.f_count);

	if (sendto(s, fptr, len, 0, toaddr, tolen) < 0)
		return (SYSERR);

	return OK;
}
