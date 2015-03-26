// scanf.c - scanf, fscanf, sscanf, getch, ungetch, sgetch, sungetch

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <tty.h>

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
getch(int dev, int *buf)
{
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
ungetch(int dev, int *buf)
{
	return *buf = EMPTY;
}
/*------------------------------------------------------------------------
 *  scanf  --  read from the console according to a format
 *------------------------------------------------------------------------
 */
int
scanf(char *fmt, int args)
{
	int getch();
	int ungetch();
	int buf;

	buf = EMPTY;
	return (_doscan(fmt, &args, getch, ungetch, CONSOLE, &buf));
}

//------------------------------------------------------------------------
//  fscanf  --  read from a device (file) according to a format
//------------------------------------------------------------------------
int
fscanf(int dev, char *fmt, int args)
{
	int getch();
	int ungetch();
	int buf;

	buf = EMPTY;
	return (_doscan(fmt, &args, getch, ungetch, dev, &buf));
}

//------------------------------------------------------------------------
//  sgetch  -- get the next character from a string
//------------------------------------------------------------------------
static int
sgetch(int dummy, char **cpp)
{
	return (*(*cpp) == '\0' ? EOF : *(*cpp)++);
}

//------------------------------------------------------------------------
//  sungetc  --  pushback a character in a string
//------------------------------------------------------------------------
static int
sungetch(int dummy, char **cpp)
{
	return (*(*cpp)--);
}

//------------------------------------------------------------------------
//  sscanf  --  read from a string according to a format
//------------------------------------------------------------------------
int
sscanf(char *str, const char *fmt, int args)
{
	char *s;

	s = str;
	return (_doscan(fmt, &args, sgetch, sungetch, 0, &s));
}
