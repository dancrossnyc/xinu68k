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
	char ch;
	char *to;
	char quote;

	to = Shl.shargst;	// area to place token strings
	tokptr = &Shl.shtok[0];	// array of ptrs to tokens
	ntok = 0;		// no tokens
	for (p = line; *p != '\0' && *p != '\n' && ntok < SHMAXTOK;) {
		while ((ch = *p) == ' ')	// skip leading blanks
			p++;
		if (ch == '\0' || ch == '\n')	// end of line or string
			return ntok;
		*tokptr++ = to;	// save start of token
		Shl.shtktyp[ntok++] = ch;
		if (ch == '"' || ch == '\'') {	// check for quoted str.
			quote = ch;
			for (p++;
			     (ch = *p++) != quote &&
			     ch != '\n' && ch != '\0';)
				*to++ = ch;
			if (ch != quote)
				return SYSERR;
		} else {	// other possible tokens
			*to++ = *p++;
			if (ch != '>' && ch != '<' && ch != '&') {
				ch = *p;
				while (ch != '\0' &&
				       ch != '\n' &&
				       ch != '<' &&
				       ch != '>' &&
				       ch != ' ' &&
				       ch != '"' &&
				       ch != '\'' && ch != '&') {
					*to++ = *p++;	// copy alphamerics
					ch = *p;
				}
			}
		}
		*to++ = '\0';	// terminate token string
	}

	return ntok;
}
