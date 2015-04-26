|------------------------------------------------------------------------
| clkint  --  real-time clock interrupt service routine
|
| If we jump into C, we must save D0, D1, A0 and A1.
|------------------------------------------------------------------------
.text
.globl	clkint
clkint:
	| XXX Hack for simulator.
	move.l	%a0,-(%sp)
	lea	0x100100,%a0
	bclr.b	#0,20(%a0)		| Acknowledge interrupt.
	bset.b	#0,(%a0)
	move.l	(%sp)+,%a0
	|
	subi.l	#1,clock6		| Is this the 6th interrupt?
	bgt	Lout			|  no => return
	move.l	#6,clock6		|  yes=> reset counter&continue
	subi.l	#1,ticks10		| Is this 10th tick?
	bgt	Lchkdefer		|  no => process tick
	move.l	#10,ticks10		|  yes=> reset counter&continue
	addi.l	#1,clktime		| increment time-of-day clock
Lchkdefer:
	tst.l	deferclock		| Are clock ticks deferred?
	beq	Lnodefer		|  no => go process this tick
	addi.l	#1,clkdiff		|  yes=> count in clkdiff and
	rte				|        return quickly
Lnodefer:
	movem.l	%d0-%d1/%a0-%a1,-(%sp)	| (Likely to call C, so save regs.)
	tst.l	slnempty		| Is sleep queue nonempty?
	beq	Lpreempt		|  no => go process preemption
	movea.l	sltop,%a0		|  yes=> decrement delta key on
	subi.l	#1,(%a0)		|        first process, calling
	bgt	Lpreempt
	jsr	wakeup			|        wakeup if zero
Lpreempt:
	subi.l	#1,preempt		| Decrement preemption counter
	bgt	Lreturn			|   and call resched if it
	jsr	resched			|   reaches zero
Lreturn:
	movem.l	(%sp)+,%d0-%d1/%a0-%a1
Lout:
	rte				| Return from interrupt
