; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/kernel/isr_asm.asm
global isr0
global isr1
extern isr_handler

section .text

; Common ISR stub
isr_common_stub:
    pusha
    mov ax, ds
    push eax
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_handler
    
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa
    add esp, 8
    iret

; ISR handlers
isr0:
    push byte 0    ; Push dummy error code
    push byte 0    ; Push interrupt number
    jmp isr_common_stub

isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub