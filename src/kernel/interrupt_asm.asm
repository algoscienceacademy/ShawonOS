; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/kernel/interrupt_asm.asm
global interrupt_handler_0
global interrupt_handler_1
global default_interrupt_handler
extern interrupt_handler_main

section .text

%macro INTERRUPT_HANDLER 1
    push dword %1    ; Push interrupt number
    pushad          ; Push all general purpose registers
    call interrupt_handler_main
    popad           ; Restore all general purpose registers
    add esp, 4      ; Clean up interrupt number
    iret            ; Return from interrupt
%endmacro

interrupt_handler_0:
    INTERRUPT_HANDLER 0

interrupt_handler_1:
    INTERRUPT_HANDLER 1

default_interrupt_handler:
    INTERRUPT_HANDLER 0xFF