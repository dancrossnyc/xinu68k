#define	FLREAD		0x01	// file mode bit for "read"
#define	FLWRITE		0x02	// file mode bit for "write"
#define	FLRW		0x03	// file mode bits for read+write
#define	FLNEW		0x08	// file mode bit for "new file"
#define	FLOLD		0x10	// file mode bit for "old file"

// Definition of characters in the mode argument to open
#define	FLOMODE		'o'	// Old  => file exists
#define	FLNMODE		'n'	// New  => file does not exist
#define	FLRMODE		'r'	// Read => open read-only
#define	FLWMODE		'w'	// Write=> open for writing

// Universal file control functions (additional args in parentheses)
#define	FLREMOVE	3001	// remove file (name)
#define	FLACCESS	3002	// test access (name, mode)
#define	FLRENAME	3003	// change file name (old, new)
