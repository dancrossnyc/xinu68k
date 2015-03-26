// fputs.c - fputs

//------------------------------------------------------------------------
//  fputs  --  write a null-terminated string to a device (file)
//------------------------------------------------------------------------
int
fputs(int dev, char *s)
{
	int r;
	int c;
	int putc(int, int);

	r = 0;
	while ((c = *s++) != '\0')
		r = putc(dev, c);

	return r;
}
