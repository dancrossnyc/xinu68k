#include "conf.h"
#include "kernel.h"
#include "network.h"
#include "rwho.h"

struct rwinfo Rwho;		// all globals used by rwho subsystem

//------------------------------------------------------------------------
//  rwho  -  Initialize rwho subsystem and start daemon processes
//------------------------------------------------------------------------
void
rwho(void)
{
	resume(create(RWIN, RWISTK, RWIPRIO, RWINAM, RWIARGS));
	resume(create(RWOUT, RWOSTK, RWOPRIO, RWONAM, RWOARGS));
}
