/* fprintf.c - fprintf */

#define	OK	1

/*------------------------------------------------------------------------
 *  fprintf  --  print a formatted message on specified device (file)
 *------------------------------------------------------------------------
 */
int
fprintf(int dev, char *fmt, int args)
{
	int putc();

	_doprnt(fmt, &args, putc, dev);
	return (OK);
}
