#include "u.h"
#include "fns.h"
#include "libk.h"

void
panic0(void)
{
	panic("zero");
}

void
panic(const char *msg)
{
	int ps;

	ps = disable();
	kprintf("%s", msg);
	for (;;) { ; }
	restore(ps);
}
