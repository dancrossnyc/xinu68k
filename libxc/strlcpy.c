/*
 * Inspired by Todd what's his name's version in OpenBSD.
 */
#include <stddef.h>
#include <string.h>

size_t
strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len, srclen;

	/*
	 * Get the length of the source first, test for the
	 * pathological case, then cat as much as we can.
	 */
	srclen = strlen(src);
	if (size-- <= 0)
		return(srclen);
	len = (size < srclen) ? size : srclen;
	memmove(dst, src, len);
	dst[len] = '\0';

	return(srclen);
}
