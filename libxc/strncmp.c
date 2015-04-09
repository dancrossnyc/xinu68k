// Compare strings (at most n bytes):  s1>s2: >0  s1==s2: 0  s1<s2: <0

#include <stddef.h>
#include <string.h>

int
strncmp(const char *s1, const char *s2, size_t n)
{

	while (n-- > 0 && *s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (n == 0) ? 0 : (*s1 < *--s2 ? -1 : 1);
}
