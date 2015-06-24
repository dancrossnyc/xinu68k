#include <stddef.h>
#include <string.h>

void *
memcpy(void *dst, const void *src, size_t len)
{
	return memmove(dst, src, len);
}
