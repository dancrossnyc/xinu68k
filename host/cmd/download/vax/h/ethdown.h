/* ethdown.h -- definitions for VAX ethernet down/up loader	*/

#define DLUDP		2001		/* UPD port for download	*/
#define MIN_UDPPORT	2030
#define ELOAD		"/usr/Xinu/lib/eload.vax"
#define	ETH_OK		1		/* ethernet download success	*/
#define	ETH_FAILED	-1		/* ethernet download failed	*/
#define	ETH_INITSP	0xe7000		/* initial SP value for eload	*/
#define	ETH_INITPC	0xce000		/* initial PC value for eload	*/
