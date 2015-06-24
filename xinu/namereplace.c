#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "name.h"

//------------------------------------------------------------------------
//  namrepl  -  using namespace, replace name with (newname,device)
//------------------------------------------------------------------------
SYSCALL
namereplace(char *name, char *newname, size_t size)
{
	struct nament *nptr;
	struct nament *nlast;
	int plen, rlen;
	int ps;

	ps = disable();
	memset(newname, '\0', size);
	nlast = &Nam.nametab[Nam.nnames];
	for (nptr = Nam.nametab; nptr < nlast; nptr++) {
		plen = strlen(nptr->npre);
		if (strncmp(nptr->npre, name, plen) == 0) {
			rlen = strlen(nptr->nrepl);
			if ((rlen + strlen(name) - plen) >= NAMLEN)
				break;
			strlcpy(newname, nptr->nrepl, size);
			strlcat(newname, name + plen, size);
			restore(ps);
			return nptr->ndev;
		}
	}
	restore(ps);

	return SYSERR;
}
