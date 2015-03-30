// x_reboot.c - x_reboot

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  x_reboot  -  (builtin command reboot) restart the system from scratch
 *------------------------------------------------------------------------
 */
BUILTIN
x_reboot (int stdin, int stdout, int stderr, int nargs, char *args[])
{
	restart();	// warning! This terminates everything.

	return OK;
}
