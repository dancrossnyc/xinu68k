// Definitions and constants for LSI 11 core dump files
#define	REGISTERS 	16		// number of registers
#define	NREGS		REGISTERS+1	// total regs including SR
#define	COREMAGIC	0477		// unix "magic number" for core

// header of 11 core dump file
struct core11 {
	short c_magic;			// UNIX convention
	short c_size;			// size of valid info (0=>entire
					// file contains core dump
	short c_zero1;			// padding to follow UNIX style
	short c_zero2;			// "     "    "     "    "
	uword c_regs[REGISTERS];	// dump of machine registers
	uword c_psw;			// dump of program status reg
	short c_zero3;			// more padding (as in UNIX)
	short c_zero4;			// "     "      "  "   "
	short c_zero5;			// "     "      "  "   "
					// Core image follows header
};
