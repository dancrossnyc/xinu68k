#include "u.h"

// standard serial line unit device constants
#define	SLUENABLE	0x40	// device interrupt enable bit
#define	SLUREADY	0x80	// device ready bit
#define	SLUDISABLE	0000	// device interrupt disable mask
#define	SLUTBREAK	0x01	// transmitter break-mode bit
#define	SLUERMASK	0xF000	// mask for error flags on input
#define	SLUCHMASK	0xFF	// mask for input character

// SLU device register layout and correspondence to vendor's names
struct csr {
	byte cmrxa;		// Control register
	union {
		byte crstat;	// receiver control and status  (RCSR)
		byte ctstat;	// transmitter control and status
	};
	byte crdna0;		// Do not access
	union {
		byte crbuf;	// receiver data buffer         (RBUF)
		byte ctbuf;	// transmitter data buffer      (XBUF)
	};
	union {
		byte cipcr;
		byte cacr;
	};
	union {
		byte cisr;	// Interrupt status register
		byte cimr;	// Interrupt mask register
	};
};
