// Returns the number of
// non-NULL bytes in string argument.

int
strlen(char *s)
{
	int n;

	n = 0;
	while (*s++)
		n++;
	return (n);
}
