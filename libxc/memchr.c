// ISO C.

#include <stddef.h>
#include <string.h>

void *
memchr(const void *p, int v, size_t len)
{
	const char *b = (const char *)p;

	while (len > 0) {
		if (*b == v) {
			return (void *)b;
		}
		len--;
		b++;
	}

	return NULL;
}
