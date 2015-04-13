#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  x_echo  -  (command echo) echo arguments separated by blanks
//------------------------------------------------------------------------
COMMAND
x_echo(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char str[80];
	int i;

	str[0] = NULLCH;
	if (nargs != 1) {
		for (strcpy(str, args[1]), i = 2; i < nargs; i++) {
			strcat(str, " ");
			strcat(str, args[i]);
		}
	}
	strcat(str, "\n");
	write(stdout, str, strlen(str));

	return OK;
}
