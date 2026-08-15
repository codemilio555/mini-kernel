section .multiboot
align 8
multiboot_start:
	dd 0xe85250d6
	dd 0x0
	dd multiboot_end - multiboot_start
	dd -(0xe85250d6 + 0 + (multiboot_end - multiboot_start))

	dw 0
	dw 0
	dd 8

multiboot_end:

bits 32

section .text
global _start
extern main

_start:
	cli
	mov esp, stack_top
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
