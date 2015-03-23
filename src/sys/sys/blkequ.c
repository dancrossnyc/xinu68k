/* blkequ.c - blkequ */

#include <kernel.h>

/*------------------------------------------------------------------------
 *  blkequ  -  return TRUE iff one block of memory is equal to another
 *------------------------------------------------------------------------
 */
int
blkequ(char *first, char *second, int nbytes)
{
	while (--nbytes >= 0)
		if (*first++ != *second++)
			return (FALSE);
	return (TRUE);
}
