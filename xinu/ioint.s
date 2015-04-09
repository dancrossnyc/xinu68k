| I/O interrupts trap here.  Original PC and PS are on top of the
| stack upon entry.  Low order 4 bits of the current PS contain the
| device descriptor.  Interrupts are disabled.

.text
.globl	inint,outint,intmap
outint:					| Output interrupt
	br	ioint
inint:					| Input interrupt
ioint:					| Code common to input & output
	rte
