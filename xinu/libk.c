#include "u.h"
#include "libk.h"

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

void *
memcpy(void *dst, const void *src, size_t len)
{
	return memmove(dst, src, len);
}

int
memcmp(const void *a, const void *b, size_t len)
{
	const char *aa = (const char *)a;
	const char *bb = (const char *)b;

	while (len-- > 0) {
		if (*aa < *bb)
			return -1;
		if (*aa > *bb)
			return 1;
		aa++;
		bb++;
	}

	return 0;
}

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
