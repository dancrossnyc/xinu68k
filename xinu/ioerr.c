// ioerr.c - ioerr, interr

#include <conf.h>
#include <kernel.h>

//------------------------------------------------------------------------
//  ioerr  -  return an error (used for "error" entries in devtab)
//------------------------------------------------------------------------
int
ioerr(void)
{
	return (SYSERR);
}

INTPROC
interr(void)
{
}
