// mem.h - freestk, roundew, truncew

/*----------------------------------------------------------------------
 * roundew, truncew - round or truncate address to next even word
 *----------------------------------------------------------------------
 */
#define	roundew(x)	(void *)((3 + (uword)(x)) & (~3) )
#define	truncew(x)	(void *)(((uword)(x)) & (~3))

/*----------------------------------------------------------------------
 *  freestk  --  free stack memory allocated by getstk
 *----------------------------------------------------------------------
 */
#define freestk(p,len)	freemem((char *)(p)			\
				- (unsigned)(roundew(len))	\
				+ (unsigned)sizeof(int),	\
				(unsigned)roundew(len) )

struct	mblock	{
	struct	mblock	*mnext;
	unsigned mlen;
	};
extern	struct	mblock	memlist;	// head of free memory list
extern	char	*maxaddr;		// max memory address
extern	int	etext;			// address beyond text segment
extern	int	edata;			// address beyond data segment
extern	int	end;			// address beyond loaded memory

