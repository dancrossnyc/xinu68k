#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  devdump  -  dump device names from the device switch table
//------------------------------------------------------------------------
void
devdump(void)
{

	kprintf("Num  Device   minor   CSR    i-vector o-vector I/O buffer\n");
	kprintf("--- --------  ----- -------- -------- -------- ----------\n");
	for (int k = 0; k < NDEVS; k++) {
		struct devsw *dp = &devtab[k];
		kprintf("%2d. %-9s %3d   %08x %08x %08  %08x\n",
			k, dp->name, dp->minor,
			dp->csr, dp->ivec, dp->ovec,
			dp->iobuf);
	}
}
