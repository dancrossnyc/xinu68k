/*
 * Libk.
 */

#include <u.h>
#include <libk.h>

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

// Things that should be elsewhere.
void clkint() { }
void setclkr() { }
void inint() { }
void outint() { }
void restart() { }
void ctxsw() { }

unsigned short
cksum(unsigned short *p, size_t words)
{
	u32 sum;

	sum = 0;
	for (int k = 0; k < words; k++) {
		sum += *p++;
	}
	while ((sum >> 16) != 0)
		sum = (sum >> 16) + (sum & 0xFFFF);

	return (~sum) & 0xFFFF;
}

void
panic(const char *msg)
{
	int ps;

	disable(ps);
	printf("%s", msg);
	for (;;) { ; }
	restore(ps);
}
