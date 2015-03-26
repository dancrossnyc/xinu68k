// Seek.c - Seek

#include "fs.h"

//------------------------------------------------------------------------
//  Seek - seek in a file given its index in the file cache table
//------------------------------------------------------------------------
int
Seek(int rfd, long newpos)
{
	long lseek();
	long pos;

	if ((pos = lseek(fcache[rfd].fd, newpos, 0)) < 0)
		return (SYSERR);
	fcache[rfd].currpos = pos;
	return (OK);
}
