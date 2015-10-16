#include "conf.h"
#include "kernel.h"
#include "date.h"

//------------------------------------------------------------------------
// gettime - get local time in seconds past Jan 1, 1970
//------------------------------------------------------------------------
SYSCALL
gettime(long *timvar)
{
	long now;

	if (getutime(&now) == SYSERR)
		return SYSERR;
	*timvar = ut2ltime(now);	// adjust for timezone
	return OK;
}
