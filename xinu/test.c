#include "conf.h"
#include "kernel.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  main  --  start UDP echo server and then run Xinu pseudo-shell
 *------------------------------------------------------------------------
 */
int
main(void)
{
	int udpecho();

	// start rwho daemon and input processes
	rwho();

	// start UDP echo server
	resume(create(udpecho, 380, 30, "UDPecho", 0));

	while (TRUE) {
		login(CONSOLE);
		shell(CONSOLE);
	}
}
