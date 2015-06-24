#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "mark.h"
#include "bufpool.h"

//------------------------------------------------------------------------
// x_bpool - (command bpool) format and print buffer pool information
//------------------------------------------------------------------------
COMMAND
x_bpool(int stdin, int stdout, int stderr, int nargs, char *args[])
{

	for (int i = 0; i < nbpools; i++) {
		struct bpool *bpptr = &bptab[i];
		char str[80];
		sprintf(str, "pool=%2d. bsize=%4d, sem=%2d, count=%d\n",
			i, bpptr->bpsize, bpptr->bpsem,
			scount(bpptr->bpsem));
		write(stdout, str, strlen(str));
	}

	return OK;
}
