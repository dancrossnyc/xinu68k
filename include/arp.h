// arp.h

// DARPA Internet Address Resolution Protocol  (see RFCs 826, 920)

#define	AR_HRD	1		// Ethernet hardware type code
#define	AR_PROT	0x0800		// IP protocol address code
#define	AR_HLEN	6		// Ethernet physical address length
#define	AR_PLEN	4		// IP Protocol address length
#define	AR_TAB	6		// size of IP-to-Ether addr. cache (>1)
#define	AR_TIME	60		// time to wait for reply in 1/10 secs
#define	AR_RTRY	2		// num. of times to try an arp request

// Definitions of codes used in operation field of ARP packet

#define	AR_REQ	1		// arp request to resolve address
#define	AR_RPLY	2		// reply to a resolve request
#define	AR_RREQ	3		// reverse ARP request (RARP packets)
#define	AR_RRLY	4		// reply to a reverse request (RARP ")

struct	arppak	{		// format of DARPA ARP packet
	short	ar_hrd;		// type of hardware (Ethernet = 1)
	short	ar_prot;	// format of proto. address (IP=0x0800)
	char	ar_hlen;	// hardware address length (6 for Ether)
	char	ar_plen;	// protocol address length (4 for IP)
	short	ar_op;		// arp operation (see list above)
	Eaddr	ar_sha;		// sender's physical hardware address
	IPaddr	ar_spa;		// sender's protocol address (IP addr.)
	Eaddr	ar_tha;		// target's physical hardware address
	IPaddr	ar_tpa;		// target's protocol address (IP)
};

// Format of the IP-to-Ethernet address resolution cache

enum ArpStates {
	ARP_FREE,	// Entry is unused (initial value)
	ARP_USED,	// Entry is used but route still unknown
	ARP_REMOTE,	// Entry is reachable only by gateway
	ARP_RESOLVED,	// Entry has been resolved to Eth. addr.
	ARP_NSTATES
};

struct	arpent	{		// format of entry in ARP cache
	enum ArpStates state;	// state of this entry (see below)
	Eaddr ether_addr;	// Ethernet address of this host
	IPaddr ip_addr;		// IP address of this host
	int dev;		// Xinu device for this host route
};

struct	arpblk	{		// all information about ARP cache
	struct arpent arptab[AR_TAB]; // IP-to-Ethernet address cache
	int	atabsiz;	// current entries in arptab
	int	atabnxt;	// next position in arptab to use
	int	arpsem;		// semaphore for access to ARP service
	int	arppid;		// id of process waiting for ARP reply
	IPaddr	arpwant;	// IP addr. process waiting to resolve
	int	rarppid;	// id of process waiting for RARP reply
	int	rarpsem;	// semaphore for access to RARP service
};

extern	struct	arpblk	Arp;
