// a.out.h

#include "u.h"

struct	exec {			// a.out header
	i16	a_magic;	// magic number
	u16	a_text;		// size of text segment
	u16	a_data;		// size of initialized data
	u16	a_bss;		// size of uninitialized data
	u16	a_syms;		// size of symbol table
	u16	a_entry;	// entry point
	u16	a_unused;	// not used
	char	a_flag;		// relocation info stripped
	char	a_v6;		// UNIX V6 compatibility  mode
};

#define	A_MAGIC1	0407	// normal
#define	A_MAGIC2	0410	// read-only text
#define	A_MAGIC3	0411	// separated I&D
#define	A_MAGIC4	0405	// overlay

struct	nlist {			// symbol table entry
	char	n_name[8];	// symbol name
	uword	n_type;		// type flag
	uword	n_value;	// value
};

// values for type flag

#define	N_UNDF		0	// undefined
#define	N_ABS		01	// absolute
#define	N_TEXT		02	// text symbol
#define	N_DATA		03	// data symbol
#define	N_BSS		04	// bss symbol
#define	N_TYPE		037
#define	N_REG		024	// register name
#define	N_FN		037	// file name symbol
#define	N_EXT		040	// external bit, or'ed in
#define	FORMAT		"%06o"	// to print a value
