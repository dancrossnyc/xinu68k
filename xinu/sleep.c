#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "q.h"
#include "sleep.h"

//------------------------------------------------------------------------
// sleep  --  delay the calling process n seconds
//------------------------------------------------------------------------
SYSCALL
sleep(int n)
{
	int ps;

	if (n < 0 || !hasclock)
		return SYSERR;
	if (n == 0) {
		ps = disable();
		resched();
		restore(ps);
		return OK;
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10 * n);

	return OK;
}
