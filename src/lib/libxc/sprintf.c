/* sprintf.c - sprintf */

/*------------------------------------------------------------------------
 *  sprintf  --  format arguments and place output in a string
 *------------------------------------------------------------------------
 */
char *
sprintf(char *str, char *fmt, int args)
{
	int sprntf();
	char *s;

	s = str;
	_doprnt(fmt, &args, sprntf, &s);
	*s++ = '\0';
	return (str);
}

/*------------------------------------------------------------------------
 *  sprntf  --  routine called by doprnt to handle each character
 *------------------------------------------------------------------------
 */
static
sprntf(char **cpp, int c)
{
	return (*(*cpp)++ = c);
}
