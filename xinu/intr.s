| Disable interrupts.
.globl disable
disable:
	move.w	%sr,%d0
	move.w	#0x2700,%sr
	rts

| Restore interrupt status from the given argument.
.globl restore
restore:
	move.w	4(%sp),%sr
	rts

| Unconditionally enable interrupts.
.global enable
enable:
	move.w	#0x2000,%sr
	rts
