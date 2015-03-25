// printf.c - printf

#include <stdarg.h>

#define	OK	1
#define	CONSOLE	0

//------------------------------------------------------------------------
//  printf  --  write formatted output on CONSOLE 
//------------------------------------------------------------------------
int
printf(const char *fmt, ...)
{
	va_list args;
	int putc();

	va_start(args, fmt);
	_doprnt(fmt, &args, putc, CONSOLE);
	va_end(args);

	return OK;
}
