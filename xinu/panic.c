#include "u.h"
#include "fns.h"
#include "libk.h"

void
panic(const char *msg)
{
	uword ps;

	ps = disable();
	printf("%s", msg);
	for (;;) { ; }
	restore(ps);
}
