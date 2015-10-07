| Pause the processor until we get an interrupt.
.text
.globl pause, halt
halt:
pause:
	STOP	#0x2000
	RTS

.text
.globl stop
stop:
	STOP	#0x2700
	RTS
