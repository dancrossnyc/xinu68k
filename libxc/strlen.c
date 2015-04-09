// Returns the number of
// non-NULL bytes in string argument.

#include <stddef.h>
#include <string.h>

size_t
strlen(const char *s)
{
	size_t n;

	n = 0;
	while (*s++)
		n++;

	return n;
}
