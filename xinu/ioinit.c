#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
// iosetvec -- fill in interrupt vectors and dispatch table entries
//------------------------------------------------------------------------
int
iosetvec(int descrp, void *incode, void *outcode)
{
	struct devsw *devptr;
	struct intmap *map;
	struct vector *vptr;

	if (isbaddev(descrp))
		return SYSERR;
	devptr = &devtab[descrp];
	map = &intmap[devptr->num];	// fill in interrupt dispatch
	map->intr = devptr->intr;	//   map with addresses of high-
	map->icode = (uword)incode;	//   level input and output
	vptr = (struct vector *)devptr->ivec;
	vptr->vproc = ioint;		// fill in input interrupt
	vptr->vps = descrp | DISABLE;	//   vector PC and PS values
	return OK;
}
