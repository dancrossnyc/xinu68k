/* printf.c - printf */

#define	OK	1
#define	CONSOLE	0

/*------------------------------------------------------------------------
 *  printf  --  write formatted output on CONSOLE 
 *------------------------------------------------------------------------
 */
int
printf(char *fmt, int args)
{
	int putc();

	_doprnt(fmt, &args, putc, CONSOLE);
	return (OK);
}
