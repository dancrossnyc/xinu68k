#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

//------------------------------------------------------------------------
//  ethwstrt - start an ethernet write operation on the DEQNA
//------------------------------------------------------------------------

void
ethwstrt(struct etblk *etptr, char *buf, int len, int setup)
{
	struct dcmd *dcmptr;
	struct dqregs *dqptr;

	dqptr = etptr->eioaddr;
	//while (!(dqptr->d_csr & DQ_XLI));	// XXX Hack for simulator.
	etptr->etwtry = EXRETRY;
	dcmptr = etptr->ewcmd;
	dcmptr->dc_bufh = DC_VALID | DC_ENDM | (etptr->etsetup = setup);
	if (isodd(len))
		dcmptr->dc_bufh |= DC_LBIT;
	dcmptr->dc_buf = buf;
	dcmptr->dc_len = dqlen(len);
	dcmptr->dc_st1 = dcmptr->dc_st2 = DC_INIT;
	dcmptr->dc_flag = DC_NUSED;
	dqptr->d_wcmd = (char *)dcmptr;
	dqptr->d_wcmdh = NULL;
}
