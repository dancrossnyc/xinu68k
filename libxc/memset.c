#include <stddef.h>
#include <string.h>

void *
memset(void *dst, int c, size_t len)
{
	unsigned char *p = (unsigned char *)p;
	unsigned char v = c;

	while (len-- > 0) {
		*p++ = v;
	}

	return dst;
}
