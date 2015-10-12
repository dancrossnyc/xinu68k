#include "conf.h"
#include "kernel.h"
#include "shell.h"

//------------------------------------------------------------------------
// lexan - ad hoc lexical analyzer to divide command line into tokens
//------------------------------------------------------------------------
int
lexan(char *line)
{
	char **tokptr;
	int ntok;
	char *p;
	char *to;
	char quote;

	to = Shl.shargst;	// area to place token strings
	tokptr = &Shl.shtok[0];	// array of ptrs to tokens
	ntok = 0;		// no tokens
	for (p = line; *p != '\0' && *p != '\n' && ntok < SHMAXTOK;) {
		while (*p == ' ' || *p == '\t')	// skip leading blanks
			p++;
		if (*p == '\0' || *p == '\n')	// end of line or string
			return ntok;
		ntok++;				// found a new token
		*tokptr++ = to;			// save start of token
		Shl.shtktyp[ntok] = *p;
		if (*p == '"' || *p == '\'') {	// check for quoted str.
			quote = *p++;
			while (*p != quote && *p != '\n' && *p != '\0')
				*to++ = *p++;
			if (*p != quote)	// check for end quote
				return SYSERR;
			p++;			// skip terminating quote
		} else {			// other possible tokens
			*to++ = *p++;
			if (*p != '>' && *p != '<' && *p != '&') {
				while (*p != '\0' &&
				       *p != '\n' &&
				       *p != '<' &&
				       *p != '>' &&
				       *p != ' ' &&
				       *p != '"' &&
				       *p != '\'' &&
				       *p != '&') {
					*to++ = *p++;	// copy alphamerics
				}
			}
		}
		*to++ = '\0';			// terminate token string
	}

	return ntok;
}
