#include "u.h"
#include "fns.h"

void
panic(const char *msg)
{
	int ps;

	ps = disable();
	kprintf("%s\n", msg);
	prdump();
	for (;;) { pause(); }
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

volatile void *intrargs[256];

void
lowcore(void)
{
	volatile uword *vectors = (uword *)0;

	for (int k = 0; k < 256; k++) {
		vectors[k] = (uword)panice;
		intrargs[k] = (void *)0;
	}
	vectors[0] = 0x100000 - 4;
	vectors[1] = (uword)panic0;
}
