/* blkcopy.c - blkcopy */

#include <kernel.h>

/*------------------------------------------------------------------------
 *  blkcopy  -  copy a block of memory form one location to another
 *------------------------------------------------------------------------
 */
int
blkcopy(char *to, char *from, int nbytes)
{
	while (--nbytes >= 0)
		*to++ = *from++;
	return(OK);
}
