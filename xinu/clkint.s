|------------------------------------------------------------------------
| clkint  --  real-time clock interrupt service routine
|
| If we jump into C, we must save D0, D1, A0 and A1.
|------------------------------------------------------------------------

/*
// XXX Hack for simulator.
static void
mclk_start(void)
{
#define	TIMER_CTL_REG		0
#define	TIMER_INTVEC_REG	2
#define	TIMER_PRELOAD_REG	4
#define	TIMER_VECTOR_NUM	64
#define	TIMER_TICKS		(125000/60)	// 60 times per second.
#define	TIMER_INIT		0xA0
	volatile byte *timer = (byte *)0x100040;
	uword ticks = (uword)TIMER_TICKS;
	timer[TIMER_INTVEC_REG] = TIMER_VECTOR_NUM;
	// The next four statements simulate the 'MOVEP.L'
	// instruction. The naive sequence:
	// *(uword *)(timer + TIMER_PRELOAD_REG) = TIMER_TICKS;
	// won't work due to the specifics of the MC68230 timer
	// (as implemented in the simiulator).
	timer[TIMER_PRELOAD_REG + 0] = (ticks >> 24) & 0xFF;
	timer[TIMER_PRELOAD_REG + 2] = (ticks >> 16) & 0xFF;
	timer[TIMER_PRELOAD_REG + 4] = (ticks >>  8) & 0xFF;
	timer[TIMER_PRELOAD_REG + 6] = (ticks >>  0) & 0xFF;
	timer[TIMER_CTL_REG] = TIMER_INIT;
	timer[TIMER_CTL_REG] |= 0x01;
	void mclkstart();
	mclkstart();
}
*/

.text
| XXX Hack for simulator.
.globl mclkstart
mclkstart:
	lea	0x100040,%a0		| Load address of timer ctl dev into A0
	move.b	#64,2(%a0)		| Vector num 64 into vec num register
	move.l	#(125000),%d0		| Clock ticks 60 times / second
	movep.l	%d0,4(%a0)		| Set preload register
	move.b	#0xA0,0(%a0)		| Set ctl register to init timer
	bset.b	#0,0(%a0)		| Start timer
	rts

.globl	clkint
clkint:
	| XXX Hack for simulator.
	move.l	%a0,-(%sp)
	lea	0x100040,%a0
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
