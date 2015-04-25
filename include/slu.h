// standard serial line unit device constants
#define	SLUENABLE	0x40	// device interrupt enable bit
#define	SLUREADY	0x80	// device ready bit
#define	SLUDISABLE	0000	// device interrupt disable mask
#define	SLUTBREAK	0x01	// transmitter break-mode bit
#define	SLUERMASK	0xF000	// mask for error flags on input
#define	SLUCHMASK	0xFF	// mask for input character

// SLU device register layout and correspondence to vendor's names
struct csr {
	int crstat;		// receiver control and status  (RCSR)
	int crbuf;		// receiver data buffer         (RBUF)
	int ctstat;		// transmitter control & status (XCSR)
	int ctbuf;		// transmitter data buffer      (XBUF)
};
