#include "conf.h"
#include "kernel.h"
#include "name.h"

#ifndef	RFILSYS
#define	RFILSYS	SYSERR
#endif
#ifdef	Nnsys
struct nam Nam;
#endif

//------------------------------------------------------------------------
// nameinit - initialize the syntactic namespace pseudo-device
//------------------------------------------------------------------------
void
nameinit(void)
{
	Nam.nnames = 0;

	// Xinu namespace definition.
	mount("", NAMESPACE, "Xinu/storage/");
	mount("Xinu/", RFILSYS, "/usr/Xinu/");
	mount("h/", NAMESPACE, "Xinu/src/sys/h/");
	mount("kernel/", NAMESPACE, "Xinu/src/sys/sys/");
	mount("core11", NAMESPACE, "kernel/core11");
	mount("a.out", NAMESPACE, "kernel/a.out");
	mount("/dev/console", CONSOLE, NULLSTR);
	mount("/dev/null", RFILSYS, "/dev/null");
	mount("/dev/", SYSERR, NULLSTR);
	mount("/", RFILSYS, "/");
	mount("~/", NAMESPACE, "Xinu/");
}
