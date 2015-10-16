#include <stddef.h>
#include <string.h>

#include "conf.h"
#include "kernel.h"
#include "date.h"
#include "shell.h"

//------------------------------------------------------------------------
// x_who - (command who) print name user is logged in under
//------------------------------------------------------------------------
COMMAND
x_who(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	char machine[32];
	char str[80];

	if (marked(Shl.shmark) && Shl.shused) {
		getname(machine, sizeof(machine));
		sprintf(str, "%10s!%-10s Console : ", machine, Shl.shuser);
		write(stdout, str, strlen(str));
		ascdate(ut2ltime(Shl.shlogon), str);
		strlcat(str, "\n", sizeof(str));
		write(stdout, str, strlen(str));
	}

	return OK;
}
