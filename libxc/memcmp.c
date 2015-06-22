#include <stddef.h>
#include <string.h>

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
