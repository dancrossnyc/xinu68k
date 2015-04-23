// All includes needed for the network
#include <u.h>
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

// Declarations data conversion and checksum routines
#define	hs2net(X)	(X)
#define	net2hs(X)	(X)
#define	hl2net(X)	(X)
#define	net2hl(X)	(X)
extern uint16 cksum(void *p, size_t nwords);	// 1s comp of 16-bit 2s comp sum
