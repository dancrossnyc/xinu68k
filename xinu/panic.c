#include "u.h"
#include "fns.h"
#include "libk.h"

void
panic(const char *msg)
{
	int ps;

	ps = disable();
	kprintf("%s", msg);
	for (;;) { ; }
	restore(ps);
}

void
panic0(void)
{
	panic("zero");
}

void
panice(void)
{
	panic("unhandled exception");
}

void
lowcore(void)
{
	volatile uword *vectors = (uword *)0;

	vectors[0] = 0x100000 - 4;
	vectors[1] = (uword)panic0;
	for (int k = 2; k < 64; k++) {
		vectors[k] = (uword)panice;
	}
}
