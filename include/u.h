// u.h - Types and useful constants.

#ifndef U_H__
#define U_H__

#include "stddef.h"

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long ulong;
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef int word;		// Register word.
typedef unsigned int uword;

//
typedef uint32 DBADDR;

// Symbolic constants used throughout Xinu
typedef char Bool;		// Boolean type
#define	FALSE		0	// Boolean constants
#define	TRUE		1
#define	NULLCH		'\0'	// The null character
#define	NULLSTR		""	// Pointer to empty string
#define	SYSCALL		int	// System call declaration
#define	COMMAND		int	// Shell command declaration
#define	BUILTIN		int	// Shell builtin " "
#define	INTPROC		void	// Interrupt procedure  "
#define	PROCESS		int	// Process declaration
#define	MININT		-2147483648	// minimum integer (-2^31)
#define	MAXINT		2147483647	// maximum integer (2^31+1)
#define	LOWBYTE		0x000000FF	// mask for low-order 8 bits
#define	MINSTK		40	// minimum process stack size
#define	NULLSTK		300	// process 0 stack size
#define	DISABLE		0340	// PS to disable interrupts
#define	MAGIC		0125252	// unusual value for top of stk

enum Registers {
	PC,
	SR,
	D0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	A0,
	A1,
	A2,
	A3,
	A4,
	A5,
	A6,			// Frame pointer
	SP,			// Supervisor Stack pointer; aka A7
	USP,			// User stack pointer; aka A7
	NREGS,
};

// Universal return constants

#define	OK		 1	// system call ok
#define	SYSERR		-1	// system call failed
#define	EOF		-2	// End-of-file (usu. from read)
#define	TIMEOUT		-3	// time out  (usu. recvtim)
#define	INTRMSG		-4	// keyboard "intr" key pressed
					// (usu. defined as ^B)
// Initialization constants

#define	INITSTK		500	// initial process stack
#define	INITPRIO	20	// initial process priority
#define	INITNAME	"main"	// initial process name
#define	INITARGS	1,0	// initial count/arguments
#define	INITRET		userret	// processes return address
#define	INITSR		0x2000	// initial process PS
#define	INITREG		0	// initial register contents
#define	QUANTUM		10	// clock ticks until preemption

// Miscellaneous utility inline functions

#define	isodd(x)	(01&(int)(x))
#define	min(a,b)	( (a) < (b) ? (a) : (b) )
#define	halt()

#endif
