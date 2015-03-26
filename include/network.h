/* network.h */

/* All includes needed for the network */

#include <deqna.h>
#include <ether.h>
#include <ip.h>
#include <icmp.h>
#include <udp.h>
#include <net.h>
#include <dgram.h>
#include <arp.h>
#include <fserver.h>
#include <rfile.h>
#include <domain.h>

/* Declarations data conversion and checksum routines */

//extern	unsigned short	hs2net();	// host to network short
#define	hs2net(X)	(X)
//extern	unsigned short	net2hs();	// network to host short
#define	net2hs(X)	(X)
//extern	long		hl2net();	/* host-to-network long	
#define	hl2net(X)	(X)
//extern	long		net2hl();	// network to host long
#define	net2hl(X)	(X)
extern	long		hl2vax();	// pdp11-to-vax long
extern	long		vax2hl();	// vax-to-pdp11 long
extern	short		cksum();	// 1s comp of 16-bit 2s comp sum
