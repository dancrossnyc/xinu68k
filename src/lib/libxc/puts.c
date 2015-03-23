/* puts.c - puts */

#define CONSOLE 0

/*------------------------------------------------------------------------
 *  puts  --  write a null-terminated string to the console
 *------------------------------------------------------------------------
 */
int
puts(char *s)
{
	int c;

	while (c = *s++)
		putc(CONSOLE, c);
	return (putc(CONSOLE, '\n'));
}
