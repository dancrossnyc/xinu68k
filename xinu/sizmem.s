|------------------------------------------------------------------------
|  sizmem  --  size memory, placing highest valid address in _maxaddr
|------------------------------------------------------------------------
.globl	sizmem,maxaddr
sizmem:
	move.l	#0x00100000,%d0
	sub.l	#4,%d0
	move.l	%d0,maxaddr
	rts
