; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/kernel/isr.asm
global isr0
global isr1

section .text

; Common ISR stub that calls C handler
isr_common_stub:
    pusha           ; Push all registers
    mov ax, ds
    push eax        ; Save data segment
    
    mov ax, 0x10    ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_handler
    
    pop eax         ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa            ; Restore registers
    add esp, 8      ; Clean up error code and ISR number
    iret            ; Return from interrupt

; ISR handlers
isr0:
    push byte 0     ; Push dummy error code
    push byte 0     ; Push interrupt number
    jmp isr_common_stub

isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub