// dskbcpy.c - dskbcpy

#include <conf.h>
#include <kernel.h>
#include <disk.h>

//------------------------------------------------------------------------
//  dskbcpy  --  copy data into a new disk buffer and return its address
//------------------------------------------------------------------------
char *
dskbcpy(void *oldbuf)
{
	int i;
	char *newbuf, *to, *from;

	from = (char *)oldbuf;
	newbuf = to = getbuf(dskdbp);
	for (i = 0; i < DBUFSIZ; i++)
		*to++ = *from++;
	return (newbuf);
}
