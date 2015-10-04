#ifdef	NDEVS
#define	isbaddev(f)	((f) < 0 || (f) >= NDEVS)
#endif
#define	BADDEV		-1

// In-line I/O procedures
#define	getchar()	getc(CONSOLE)
#define	putchar(ch)	putc(CONSOLE, (ch))
#define	fgetc(unit)	getc((unit))
#define	fputc(unit, ch)	putc((unit), (ch))

extern void *intrargs[];
