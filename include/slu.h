#include "u.h"

// standard serial line unit device constants
//#define	SLUTBREAK	0x01	// transmitter break-mode bit

#define	DUART_STARTBREAK 0x06	// MR1x <- b110 => start break
#define	DUART_STOPBREAK	0x07	// MR1x <- b111 => stop break
#define	DUART_TxINTABLE	0x01	// IMR[0] is TxRDYA int control
#define	DUART_RxINTABLE	0x02	// IMR[1] is RxRDYA/full int control
#define	DUART_RxRDYA	0x01	// SRA[0] is receive ready status
#define	DUART_TxRDYA	0x04	// SRA[2] is transmit ready status
#define	DUART_ERRMASK	0xF0	// SRA mask for error flags on input
#define	DUART_CHRMASK	0xFF	// Mask for Tx/Rx character (8 bits)

// Motorola M68681 DUART device registers.
// Unions are used for the discrete names for reading and writing.
struct csr {
	union {
		byte mr1a;	// R/W: Mode Register 1 (MR1A)
		byte mr2a;	// R/W: Mode Register 2 (MR2A)
	};
	union {
		byte sra;	// R: Status Register A (SRA)
		byte csra;	// W: Clock Select Register A (CSRA)
	};
	union {
		byte dnaa;	// R: Do Not Access (A)
		byte cra;	// W: Command Register A (CRA)
	};
	union {
		byte rbufa;	// R: Rx Holding Register A (RHRA)
		byte tbufa;	// W: Tx Holding Register A (THRA)
	};
	union {
		byte ipcr;	// R: Input Port Change Register (IPCR)
		byte acr;	// W: Aux. Control Register (ACR)
	};
	union {
		byte isr;	// R: Interrupt Status Register (ISR)
		byte imr;	// W: Interrupt Mask Register (IMR)
	};
	union {
		byte ctu;	// R: Counter/Timer Upper Value (CTU)
		byte ctur;	// W: C/T Upper Preset Value (CTUR)
	};
	union {
		byte ctlv;	// R: Counter/Timer Lower Value (CTL)
		byte ctlr;	// W: C/T Lower Preset Value (CTLR)
	};
	union {
		byte mr1b;	// R/W: Mode Register 1 (MR1B)
		byte mr2b;	// R/W: Mode Register 2 (MR2B)
	};
	union {
		byte srb;	// R: Status Register B (SRB)
		byte csrb;	// W: Clock Select Register B (CSRB)
	};
	union {
		byte dnab;	// R: Do Not Access (B)
		byte crb;	// W: Command Register A (CRB)
	};
	union {
		byte rbufb;	// R: Rx Holding Register B (RHRB)
		byte tbufb;	// W: Tx Holding Register B (THRB)
	};
	byte	ivr;		// R/W: Interrupt Vector Register (IVR)
	union {
		byte	ip;	// R: Input Ports (IP0-IP5/IP6)
		byte	opcr;	// W: Output Port Conf. Register (OPCR)
	};
	union {
		byte	srcc;	// R: Start Counter Command
		byte	sopbc;	// W: Set Output Port Bits Command
	};
	union {
		byte	stcc;	// R: Stop Counter Command
		byte	ropbcl;	// Reset Output Port Bits Command
	};
};
