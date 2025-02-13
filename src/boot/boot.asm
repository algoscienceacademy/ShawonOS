; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/boot/boot.asm
MBALIGN     equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global start
extern kernel_main

bits 32
start:
    ; Set up stack
    mov esp, stack_top
    
    ; Call kernel
    call kernel_main
    
    ; Halt if kernel returns
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KB
stack_top: