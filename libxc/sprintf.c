// sprintf.c - sprintf

#include <stdarg.h>

extern void _doprnt(const char *fmt, va_list args, int (*func)(int, int), int farg);

//------------------------------------------------------------------------
//  sprntf  --  routine called by doprnt to handle each character
//------------------------------------------------------------------------
static int
sprntf(int p, int c)
{
	char **cpp = (char **)p;
	return (*(*cpp)++ = c);
}

//------------------------------------------------------------------------
//  sprintf  --  format arguments and place output in a string
//------------------------------------------------------------------------
char *
sprintf(char *str, const char *fmt, ...)
{
	va_list args;
	char *s;

	s = str;
	va_start(args, fmt);
	_doprnt(fmt, args, sprntf, (int)&s);
	va_end(args);
	*s++ = '\0';
	return (str);
}
