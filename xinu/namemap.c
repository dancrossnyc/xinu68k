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
	size_t size = 80;
	int ps;
	int dev;
	char tmpnam[NAMLEN];

	ps = disable();
	dev = namereplace(name, newname, size);
	while (dev == NAMESPACE) {
		strlcpy(tmpnam, newname, NAMLEN);
		dev = namereplace(tmpnam, newname, size);
	}
	restore(ps);

	return dev;
}
