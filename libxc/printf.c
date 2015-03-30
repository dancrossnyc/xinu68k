// printf.c - printf

#include <stdarg.h>

extern void _doprnt(const char *fmt, va_list args, int (*func)(int, int), int farg);
extern int putc(int, int);

#define	OK	1
#define	CONSOLE	0

//------------------------------------------------------------------------
//  printf  --  write formatted output on CONSOLE 
//------------------------------------------------------------------------
int
printf(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	_doprnt(fmt, args, putc, CONSOLE);
	va_end(args);

	return OK;
}
