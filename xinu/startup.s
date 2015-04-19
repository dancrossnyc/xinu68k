|------------------------------------------------------------------------
| Xinu system entry point -- first location beyond interrupt vectors
|------------------------------------------------------------------------
.data
_mystack:	.space	4*20,0
.text
.globl	start, restart, maxaddr, nulluser
restart:			| a name used by C for reboot
start:
	move.w	0x2000,%sr	| Disable interrupts
	clr.l	%d0		| Clear all CPU registers.
	clr.l	%d1
	clr.l	%d2
	clr.l	%d3
	clr.l	%d4
	clr.l	%d5
	clr.l	%d6
	clr.l	%d7
	movea.l	0,%a0
	movea.l	0,%a1
	movea.l	0,%a2
	movea.l	0,%a3
	movea.l	0,%a4
	movea.l	0,%a5
	movea.l	0,%a6
	lea	_mystack,%a7
	adda.l	#4*20,%a7
	jsr	sizmem		| Find memory size. Use initial stack.
	movea.l	maxaddr,%sp	| switch stack to high memory
	clr.l	-(%sp)		| leave space for MAGIC word
	jmp	nulluser	| Jump to C startup routine
