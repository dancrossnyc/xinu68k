#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
//  x_echo  -  (command echo) echo arguments separated by blanks
//------------------------------------------------------------------------
COMMAND
x_echo(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char str[80];

	str[0] = '\0';
	if (nargs != 1) {
		strlcpy(str, args[1], sizeof(str));
		for (int i = 2; i < nargs; i++) {
			strlcat(str, " ", sizeof(str));
			strlcat(str, args[i], sizeof(str));
		}
	}
	strlcat(str, "\n", sizeof(str));
	write(stdout, str, strlen(str));

	return OK;
}
