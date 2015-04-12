#include "conf.h"
#include "kernel.h"
#include "io.h"
#include "name.h"

#define	PADTO	24

//------------------------------------------------------------------------
//  ndump  -  dump current mappings in object naming system
//------------------------------------------------------------------------
void
ndump(void)
{

	for (int i = 0; i < Nam.nnames; i++) {
		struct nament *nptr = &Nam.nametab[i];
		int dev = nptr->ndev;
		char *p = "SYSERR";

		kprintf("\"%-s\"", nptr->npre);
		for (int len = strlen(nptr->npre); len < PADTO; len++)
			kprintf(" ");
		if (!isbaddev(dev))
			p = devtab[dev].name;
		kprintf(" -> (%-8s) \"%s\"\n", p, nptr->nrepl);
	}
}
