| Pause the processor until we get an interrupt.
.text
.globl pause
pause:
	|STOP	#0x2000
	RTS
