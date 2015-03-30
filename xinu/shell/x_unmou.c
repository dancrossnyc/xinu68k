// x_unmou.c -  x_unmou

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <name.h>

/*------------------------------------------------------------------------
 *  x_unmou  -  (command unmount) remove a prefix from the namespace table
 *------------------------------------------------------------------------
 */
COMMAND
x_unmou (int stdin, int stdout, int stderr, int nargs, char *args[])
{
	if (nargs != 2) {
		fprintf(stderr, "use: unmount prefix\n");
		return(SYSERR);
	}
	if (unmount(args[1]) == SYSERR) {
		fprintf(stderr, "unmount fails.\n");
		return(SYSERR);
	}
	return(OK);
}
