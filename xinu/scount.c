#include "conf.h"
#include "kernel.h"
#include "sem.h"

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL
scount(int sem)
{

	if (isbadsem(sem) || semaph[sem].sstate == SFREE)
		return SYSERR;

	return semaph[sem].semcnt;
}
