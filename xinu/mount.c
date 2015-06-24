#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "name.h"

//------------------------------------------------------------------------
//  mount  -  give meaning to a prefix in the abstract name space
//------------------------------------------------------------------------
SYSCALL
mount(char *prefix, int dev, char *replace)
{
	struct nament *nptr;
	struct nament *last;
	int i;
	int ps;

	if (prefix == NULL)
		prefix = NULLSTR;
	if (replace == NULL)
		replace = NULLSTR;
	if (strlen(prefix) >= NAMPLEN || strlen(replace) >= NAMRLEN)
		return SYSERR;
	ps = disable();
	for (i = 0; i < Nam.nnames; i++) {
		nptr = &Nam.nametab[i];
		if (strcmp(prefix, nptr->npre) == 0) {
			strlcpy(nptr->nrepl, replace, NAMRLEN);
			nptr->ndev = dev;
			restore(ps);
			return OK;
		}
	}
	if (Nam.nnames >= NNAMES) {
		restore(ps);
		return SYSERR;
	}
	nptr = last = &Nam.nametab[Nam.nnames++];
	if (Nam.nnames > 1) {	// preserve last name prefix
		nptr = last - 1;
		*last = *nptr;
	}
	strlcpy(nptr->npre, prefix, NAMPLEN);
	strlcpy(nptr->nrepl, replace, NAMRLEN);
	nptr->ndev = dev;
	restore(ps);

	return OK;
}
