#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
// ethread - read a single packet from the ethernet
//------------------------------------------------------------------------
int
ethread(struct devsw *devptr, char *buff, int len)
{
	int ps;
	char *wbuff;
	struct etblk *etptr;
	struct dcmd *dcmptr;

	etptr = (struct etblk *)devptr->iobuf;
	dcmptr = etptr->ercmd;
	wait(etptr->etrsem);
	ps = disable();
	etptr->etrpid = currpid;
	recvclr();
	ethrstrt(etptr, buff, len);
	while (recvtime(DQ_RTO) == TIMEOUT) {
		wbuff = (dcmptr = etptr->ewcmd)->dc_buf;
		ethstrt(etptr, (struct dqsetup *)buff);
		ethrstrt(etptr, buff, len);
		if (etptr->etlen != 0) {
			ethwstrt(etptr, wbuff, etptr->etlen, DC_NORM);
		}
	}
	if ((dcmptr->dc_st1 & DC_LUSE) == DC_ERRU) {
		len = SYSERR;
	} else {
		len =
		    (dcmptr->dc_st1 & DC_HLEN) | (dcmptr->
						  dc_st2 & DC_LLEN);
		len += DC_XLEN;
	}
	signal(etptr->etrsem);
	restore(ps);
	return len;
}
