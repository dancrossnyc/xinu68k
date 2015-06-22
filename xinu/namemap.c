#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "name.h"

//------------------------------------------------------------------------
//  namemap  -  using namespace, iteratively map name onto (newname,device)
//------------------------------------------------------------------------
SYSCALL
namemap(char *name, char *newname)
{
	int ps;
	int dev;
	char tmpnam[NAMLEN];

	ps = disable();
	dev = namrepl(name, newname);
	while (dev == NAMESPACE) {
		strcpy(tmpnam, newname);
		dev = namrepl(tmpnam, newname);
	}
	restore(ps);

	return dev;
}
