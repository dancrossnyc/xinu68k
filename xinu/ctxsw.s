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
	movem.l	%a0,-(%sp)		| Save A0 on current stack so we
					| can use an address register.  Adds
					| 4 to SP offsets. MOVEM preserves CCR.
	movea.l	8(%sp),%a0		| Move address of old save area into A0.
					| MOVEA doesn't affect CCR.
	move.w	%sr,6(%a0)		| Save SR
	clr.w	4(%a0)			| Clear the other half of that long word
	movem.l	%d0-%d7/%a0-%a7,8(%a0)	| Save all registers (including current A0)
	move.l	%usp, 72(%a0)		| Save user stack pointer
	add.l	#4,68(%a0)		| Pop old A0 off old saved stack pointer
	move.l	(%sp),40(%a0)		| Put old A0 into the save area
	move.l	4(%sp),(%a0)		| Save PC as return address
	movea.l	12(%sp),%a0		| Move address of new save area into A0
	movem.l	8(%a0),%d0-%d7/%a0-%a6	| Restore all registers but SP
	movea.l	12(%sp),%a0		| Still need temporary A0....
	movea.l	68(%a0),%sp		| Restore system stack pointer
	movea.l	72(%a0),%usp		| Restore user stack pointer
	move.l	(%a0),-(%sp)		| Move PC into return address
	move.w	6(%a0),%sr		| Restore SR
	movea.l	40(%a0),%a0		| Restore real A0. Doesn't affect CCR.
	rts				| Return to saved PC
