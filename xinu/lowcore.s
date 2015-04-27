|------------------------------------------------------------------------
| absolute location 0  -- fixed interrupt and exception vectors
|------------------------------------------------------------------------
/*
.section lowcore
.globl panic0
lowcore:
	jmp	panic0			| Jump to location zero
	.long	0x100000
*/
