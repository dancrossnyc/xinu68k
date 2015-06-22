/*
 * Inspired by the version in several other variants of Unix.
 */
#include <stddef.h>
#include <string.h>

#define	strlcat	mystrlcat

size_t
strlcat(char *dst, const char *src, size_t size)
{
	char *p;
	size_t len;

	p = memchr(dst, '\0', size);
	if (p == NULL)
		p = dst + size;
	len = p - dst;
	return(len + strlcpy(p, src, size - len));
}
