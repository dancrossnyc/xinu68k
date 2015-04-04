%{
#include "y.tab.h"
extern int brkcount, linectr;
%}
%x			COMMENT
A			[a-z_A-Z]
M			[a-z_A-Z0-9]
%%
"//".*			;
<INITIAL>{
"/*"			BEGIN(COMMENT);
}
<COMMENT>{
"*/"			BEGIN(INITIAL);
[^*\n]+			;
"*"			;
\n			linectr++;
}
"%"			{return (++brkcount == 2) ? 0 : DEFBRK;} // end-of-file or DEFBRK
":"			{return(COLON);}
0[0-9]*			{return(OCTAL);}
[1-9][0-9]+		{return(INTEGER);}
is			{return(IS);}
on			{return(ON);}
"="			;
"iint"			{return(IINT);}
"-iint"			{return(IINT);}
"oint"			{return(OINT);}
"-oint"			{return(OINT);}
"-csr"			{return(CSR);}
"csr"			{return(CSR);}
"-ivec"			{return(IVEC);}
"ivec"			{return(IVEC);}
"-ovec"			{return(OVEC);}
"ovec"			{return(OVEC);}
"-i"			{return(INIT);}
"i"			{return(INIT);}
"-o"			{return(OPEN);}
"o"			{return(OPEN);}
"-c"			{return(CLOSE);}
"c"			{return(CLOSE);}
"-r"			{return(READ);}
"r"			{return(READ);}
"-g"			{return(GETC);}
"g"			{return(GETC);}
"-p"			{return(PUTC);}
"p"			{return(PUTC);}
"-w"			{return(WRITE);}
"w"			{return(WRITE);}
"-s"			{return(SEEK);}
"s"			{return(SEEK);}
"-n"			{return(CNTL);}
"n"			{return(CNTL);}
[ \t]+			;
"\n"			{linectr++;}
{A}{M}*			{return(IDENT);}
.			{return(yytext[0]);}
