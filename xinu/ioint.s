| I/O interrupts trap here.  Original PC and PS are on top of the
| stack when one of these is called.  Interrupts are disabled.

| C functionst that are called from interrupt routines.
.globl ttyint

| intrargs is an array of pointers that are arguments passed to C.
.global intrargs

| Exception vector entry for DUART, IVR 65.
.globl vecduart
vecduart:
	movem.l	%d0-%d1/%a0-%a1,-(%sp)	| Will call C; save registers
	lea	intrargs,%a0		| Load argument pointer into A0
	adda.l	#(65*4),%a0		| and push onto the stack as C
	move.l	%a0,-(%sp)		| handler argument.
	jsr 	ttyint			| Call C
	movem.l	(%sp)+,%d0-%d1/%a0-%a1	| Restore registers
	rte				| Return from exception
