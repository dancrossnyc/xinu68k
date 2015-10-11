| I/O interrupts trap here.  Original PC and PS are on top of the
| stack when one of these is called.  Interrupts are disabled.

| C functionst that are called from interrupt routines.
.globl ttyint

| intrargs is an array of pointers that are arguments passed to C.
.globl intrargs

| Exception vector entry for DUART, IVR 65.
.globl vecduart
vecduart:
	move.w	#0x2700,%sr
	movem.l	%d0-%d1/%a0-%a1,-(%sp)	| Will call C; save registers
	lea	intrargs,%a0		| Load argument pointer into A0
	move.l	65*4(%a0),-(%sp)	| handler argument to C ttyint
	jsr 	ttyint			| Call C
	addq.l	#4,%sp			| Pop handler argument
	movem.l	(%sp)+,%d0-%d1/%a0-%a1	| Restore registers
	rte				| Return from exception
