|------------------------------------------------------------------------
|  sizmem  --  size memory, placing highest valid address in _maxaddr
|------------------------------------------------------------------------
.globl	sizmem,maxaddr
sizmem:
	move.l	#0x1000000000,%d0
	move.l	%d0,maxaddr
	rts
