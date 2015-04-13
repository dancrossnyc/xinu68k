#include "conf.h"
#include "kernel.h"

//------------------------------------------------------------------------
// x_cat - (command cat) concatenate files and write on stdout
//------------------------------------------------------------------------
COMMAND
x_cat(int stdin, int stdout, int stderr, int nargs, char *args[])
{
	int device;
	char *buf;
	int ret;
	int len;
	int i;

	if ((buf = (char *)getmem(512)) == (char *)SYSERR) {
		fprintf(stderr, "no memory\n");
		return SYSERR;
	}
	ret = OK;
	if (nargs == 1) {
		while ((len = read(stdin, buf, 512)) > 0)
			write(stdout, buf, len);
	}
	for (i = 1; i < nargs; i++) {
		if ((device = open(NAMESPACE, args[i], "ro")) == SYSERR) {
			fprintf(stderr, "Cannot open %s\n", args[i]);
			ret = SYSERR;
			break;
		}
		while ((len = read(device, buf, 512)) > 0)
			write(stdout, buf, len);
		close(device);
	}
	freemem(buf, 512);

	return ret;
}
