// puts.c - puts

#define CONSOLE 0

//------------------------------------------------------------------------
//  puts  --  write a null-terminated string to the console
//------------------------------------------------------------------------
int
puts(char *s)
{
	int c;
	int putc(int, int);

	while ((c = *s++) != '\0')
		putc(CONSOLE, c);

	return putc(CONSOLE, '\n');
}
