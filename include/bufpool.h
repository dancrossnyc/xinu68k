#include "u.h"

#ifndef	NBPOOLS
#define	NBPOOLS	5		// Maximum number of pools
#endif

#ifndef	BPMAXB
#define	BPMAXB	2048		// Maximum buffer length
#endif

#ifndef	BPMINB
#define	BPMINB	2		// Minimum buffer length
#endif

#ifndef	BPMAXN
#define	BPMAXN	100		// Maximum buffers in any pool
#endif

#ifdef	MEMMARK
extern MARKER bpmark;
#endif

struct bpool {			// Description of a single pool
	size_t bpsize;		// size of buffers in this pool
	void *bpnext;		// pointer to next free buffer
	int bpsem;		// semaphore that counts buffers
};				//  currently in THIS pool

extern struct bpool bptab[];	// Buffer pool table
extern size_t nbpools;		// current number of pools
