#include "conf.h"
#include "kernel.h"
#include "io.h"

//------------------------------------------------------------------------
//  ioinit --  standard interrupt vector and dispatch initialization
//------------------------------------------------------------------------
int
ioinit(int descrp)
{
	int minor;

	if (isbaddev(descrp))
		return SYSERR;
	minor = devtab[descrp].minor;
	iosetvec(descrp, (void *)minor, (void *)minor);
	return OK;
}

//------------------------------------------------------------------------
//  iosetvec  -  fill in interrupt vectors and dispatch table entries
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
	map->iin = devptr->iintr;	//   map with addresses of high-
	map->icode = (uword)incode;	//   level input and output
	map->iout = devptr->ointr;	//   interrupt handlers and
	map->ocode = (uword)outcode;	//   minor device numbers
	vptr = (struct vector *)devptr->ivec;
	vptr->vproc = INTVECI;		// fill in input interrupt
	vptr = (struct vector *)devptr->ovec;
	vptr->vproc = INTVECO;		// fill in output interrupt
	return OK;
}
