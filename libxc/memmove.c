#include <stddef.h>
#include <string.h>

void *
memmove(void *dst, const void *src, size_t len)
{
	char *d, *s;

	d = (char *)dst;
	s = (char *)src;
	if (d < s)
		while (len-- > 0)
			*d++ = *s++;
	else {
		d += len;
		s += len;
		while (len-- > 0)
			*--d = *--s;
	}

	return dst;
}
