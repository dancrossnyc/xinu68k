/* x_exit.c - x_exit */

#include <conf.h>
#include <kernel.h>
#include <shell.h>

/*------------------------------------------------------------------------
 *  x_exit  -  (builtin command exit) exit from the shell
 *------------------------------------------------------------------------
 */
BUILTIN
x_exit (int stdin, int stdout, int stderr, int nargs, char *args[])
{
	return(SHEXIT);
}
