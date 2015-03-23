/* fgets.c - fgets */

#define NULL    0

/*------------------------------------------------------------------------
 *  fgets  --  read a newline-terminated string from device (file) dev
 *------------------------------------------------------------------------
 */
char *
fgets(int dev, char *s, int n)
{
	int c;
	char *cs;

	cs = s;
	while (--n > 0 && (c = getc(dev)) >= 0) {
		*cs++ = c;
		if (c == '\n')
			break;
	}
	if (c < 0 && cs == s)
		return (NULL);
	*cs++ = '\0';
	return (s);
}
