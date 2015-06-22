// ISO C.

#include <stddef.h>
#include <string.h>

void *
memchr(const void *p, int v, size_t len)
{
	const char *b = (const char *)p;

	while (len > 0 && *b != v) {
		len--;
		b++;
	}

	return (void *)b;
}
