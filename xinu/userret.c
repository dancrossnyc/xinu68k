// userret.c - userret

#include <conf.h>
#include <kernel.h>

//------------------------------------------------------------------------
// userret  --  entered when a process exits by return
//------------------------------------------------------------------------
void
userret(void)
{
	kill(getpid());
}
