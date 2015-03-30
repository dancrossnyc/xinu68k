// scanf.c - scanf, fscanf, sscanf, getch, ungetch, sgetch, sungetch

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <tty.h>
#include <stdarg.h>

int _doscan(const char *fmt, va_list args, int (*getch)(int, void *),
        int (*ungetch)(int, void *), int arg1, void *arg2);

#ifndef	CONSOLE
#define	CONSOLE	0
#endif

#ifndef	EMPTY
#define	EMPTY	-1
#endif

//------------------------------------------------------------------------
//  getch  --  get a character from a device with pushback
//------------------------------------------------------------------------
static int
getch(int dev, void *b)
{
	char *buf = (char *)b;

	if (*buf != EOF && *buf != EMPTY)
		*buf = getc(dev);
	if (*buf != EOF)
		*buf = control(dev, TCNEXTC, 0);
	return (*buf);
}

//------------------------------------------------------------------------
//  ungetch  --  pushback a character for getch
//------------------------------------------------------------------------
static int
ungetch(int dev, void *b)
{
	char *buf = (char *)b;
	return *buf = EMPTY;
}

/*------------------------------------------------------------------------
 *  scanf  --  read from the console according to a format
 *------------------------------------------------------------------------
 */
int
scanf(char *fmt, ...)
{
	va_list args;
	int buf, r;

	buf = EMPTY;
	va_start(args, fmt);
	r = _doscan(fmt, args, getch, ungetch, CONSOLE, &buf);
	va_end(args);

	return r;
}

//------------------------------------------------------------------------
//  fscanf  --  read from a device (file) according to a format
//------------------------------------------------------------------------
int
fscanf(int dev, char *fmt, ...)
{
	va_list args;
	int buf, r;

	buf = EMPTY;
	va_start(args, fmt);
	r = _doscan(fmt, args, getch, ungetch, dev, &buf);
	va_end(args);

	return r;
}

//------------------------------------------------------------------------
//  sgetch  -- get the next character from a string
//------------------------------------------------------------------------
static int
sgetch(int dummy, void *p)
{
	char **cpp = (char **)p;
	return (*(*cpp) == '\0' ? EOF : *(*cpp)++);
}

//------------------------------------------------------------------------
//  sungetc  --  pushback a character in a string
//------------------------------------------------------------------------
static int
sungetch(int dummy, void *p)
{
	char **cpp = (char **)p;
	return (*(*cpp)--);
}

//------------------------------------------------------------------------
//  sscanf  --  read from a string according to a format
//------------------------------------------------------------------------
int
sscanf(char *str, const char *fmt, ...)
{
	va_list args;
	char *s;
	int r;

	s = str;
	va_start(args, fmt);
	r = _doscan(fmt, args, sgetch, sungetch, 0, &s);
	va_end(args);

	return r;
}
