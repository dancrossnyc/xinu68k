// Uncache.c - Uncache

#include "fs.h"

//------------------------------------------------------------------------
//  Uncache - remove the cached entry for a file and close the file
//------------------------------------------------------------------------
int
Uncache(char *name)
{
	int rfd;

	for (rfd = 0; rfd < MAXNFILES; rfd++) {
		if (strcmp(name, fcache[rfd].name) == 0) {
			Close(rfd);
			return (OK);
		}
	}
	return (SYSERR);
}
