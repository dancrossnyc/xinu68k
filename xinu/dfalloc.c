#include "conf.h"
#include "kernel.h"
#include "disk.h"
#include "lfile.h"

//------------------------------------------------------------------------
//  dfalloc  --  allocate a device table entry for a disk file; return id
//------------------------------------------------------------------------
int
dfalloc(void)
{				// assume exclusion for dir. provided by caller

	for (int k = 0; k < Ndf; k++) {
		if (fltab[k].fl_pid == 0) {
			fltab[k].fl_pid = getpid();
			return k;
		}
	}

	return SYSERR;
}
