section .multiboot
align 4
dd 0x1BADB002
dd 0x0
dd -(0x1BADB002)


bits 32

section .text
global _start
extern main

_start:
	cli
	mov esp, stack_top
	mov dword [0xb8000], 0x07210741
	call main

hang:
	cli
	hlt
	jmp hang

section .bss
align 16
stack_bottom:
	resb 16384
stack_top:
	align 16
section .note.GNU-stack
