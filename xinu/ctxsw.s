|------------------------------------------------------------------------
| ctxsw -- actually perform context switch, saving and loading registers
|------------------------------------------------------------------------
| The stack contains three items upon entry to this routine:
|
|	SP+8 =>	address save area with new registers + SR
|	SP+4 =>	address save area for old registers + SR
|	SP   =>	return address
|
| Stack frame:	(Offset relative to start of save area)
|	0	PC
|	4	SR (in lower 16-bit word)
|	8	D0 (aka SP)
|	12	D1 (aka FP)
|	16	D2
|	20	D3
|	24	D4
|	28	D5
|	32	D6
|	36	D7
|	40	A0
|	44	A1
|	48	A2
|	52	A3
|	56	A4
|	60	A5
|	64	A6
|	68	A7	(SSP)
|	72	A7	(USP)
|------------------------------------------------------------------------
.text
.globl	ctxsw
ctxsw:
	movem.l	%a6,-(%sp)		| Save A6 on current stack so we
					| can use an address register.  Adds
					| 4 to SP offsets. MOVEM preserves CCR.
	movea.l	8(%sp),%a6		| Move address of old save area into A6.
					| MOVEA preserves CCR
	move.w	%sr,6(%a6)		| Save SR in lower half of SR long word
	clr.w	4(%a6)			| Clear the other half of that long word
	movem.l	%d0-%d7/%a0-%a5,8(%a6)	| Save all registers except A6 and A7 (SP)
	move.l	(%sp)+,64(%a6)		| Pop old A6 from stack into the save area
	move.l	%sp,68(%a6)		| Put A7 (SP) int save area
	move.l	%usp, %a0		| Copy USP into a temporary register
	move.l	%a0, 72(%a6)		| Put user stack pointer into save area
	move.l	(%sp),(%a6)		| Put return address into save area PC
	movea.l	8(%sp),%a6		| Move address of new save area into A6
	movea.l	72(%a6),%a0		| Restore user stack pointer
	move.l	%a0,%usp
	movem.l	8(%a6),%d0-%d7/%a0-%a5	| Restore all registers but A6 and SP
	movea.l	68(%a6),%sp		| Restore system stack pointer
	move.l	(%a6),-(%sp)		| Push PC onto stack for return address
	move.w	6(%a6),%sr		| Restore status register
	movea.l	64(%a6),%a7		| Restore real A6. Preserves CCR
	rts				| Return to restored PC
