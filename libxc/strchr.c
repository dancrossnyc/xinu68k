#include <stddef.h>
#include <string.h>

char *
strchr(const char *s, int c)
{

	char *p = (char *)s;

	do {
		if (*p == c)
			return p;
	} while (*p++ != '\0');

	return NULL;
}
