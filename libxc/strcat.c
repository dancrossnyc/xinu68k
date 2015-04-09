// Concatenate s2 on the end of s1.  S1's space must be large enough.
// Return s1.

#include <stddef.h>
#include <string.h>

char *
strcat(char *s1, const char *s2)
{
	char *os1;

	os1 = s1;
	while ((*s1++) != '\0')
		;
	--s1;
	while ((*s1++ = *s2++) != '\0')
		;

	return os1;
}
