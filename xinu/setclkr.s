|------------------------------------------------------------------------
| setclkr  --  set cklruns to 1 iff real-time clock exists, 0 otherwise
|------------------------------------------------------------------------
.globl	setclkr
setclkr:
	move.l	#1,hasclock
	rts
