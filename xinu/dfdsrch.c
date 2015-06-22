#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "disk.h"
#include "lfile.h"
#include "dir.h"

//------------------------------------------------------------------------
//  dfdsrch  --  search disk directory for position of given file name
//------------------------------------------------------------------------
struct fdes *
dfdsrch(struct dsblk *dsptr, char *filename, int mbits)
{
	struct dir *dirptr;
	struct fdes *fdptr;
	int len;
	int inum;

	len = strlen(filename);
	if (len <= 0 || len >= FDNLEN)
		return (struct fdes *)SYSERR;
	dirptr = dsdirec(dsptr->dnum);
	for (int k = 0; k < dirptr->d_nfiles; k++) {
		if (strcmp(filename, dirptr->d_files[k].fdname) == 0) {
			if ((mbits & FLNEW) != 0)
				return (struct fdes *)SYSERR;
			else
				return &dirptr->d_files[k];
		}
	}
	wait(dsptr->ddirsem);
	if ((mbits & FLOLD) || dirptr->d_nfiles >= NFDES) {
		signal(dsptr->ddirsem);
		return (struct fdes *)SYSERR;
	}
	inum = ibnew(dsptr->dnum, IBNWDIR);
	fdptr = &(dirptr->d_files[dirptr->d_nfiles++]);
	fdptr->fdlen = 0L;
	strcpy(fdptr->fdname, filename);
	fdptr->fdiba = inum;
	write(dsptr->dnum, dskbcpy(dirptr), DIRBLK);
	signal(dsptr->ddirsem);

	return fdptr;
}
