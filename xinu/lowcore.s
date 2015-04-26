|------------------------------------------------------------------------
| absolute location 0  -- fixed interrupt and exception vectors
|------------------------------------------------------------------------
.section absolute
.globl panic0
lowcore:
	jmp	panic0			|     to location zero
	.long	0x100000
