// xdone.c - xdone

#include <kernel.h>

//------------------------------------------------------------------------
// xdone  --  print system completion message as last process exits
//------------------------------------------------------------------------
void
xdone(void)
{
	kprintf("\n\nAll user processes have completed.\n\n");
}
