section .data
	i	dd 0
section .text
	global _start
	_start:

l1:
	inc byte [i]
	jmp l1
