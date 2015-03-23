/*
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
 */

#define	NULL	0

char *
index(char *sp, int c)
{
	do {
		if (*sp == c)
			return (sp);
	} while (*sp++);
	return (NULL);
}
