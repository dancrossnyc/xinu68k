/* fputs.c - fputs */

/*------------------------------------------------------------------------
 *  fputs  --  write a null-terminated string to a device (file)
 *------------------------------------------------------------------------
 */
int
fputs(int dev, char *s)
{
	int r;
	int c;

	while (c = *s++)
		r = putc(dev, c);
	return (r);
}
