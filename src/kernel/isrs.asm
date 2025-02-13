; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/kernel/isrs.asm
[GLOBAL isr0]
[GLOBAL isr1]
[EXTERN isr_handler]

; ISR handlers
isr0:
    cli
    push byte 0    ; Push dummy error code
    push byte 0    ; Push interrupt number
    jmp isr_common_stub

isr1:
    cli
    push byte 0    ; Push dummy error code
    push byte 1    ; Push interrupt number
    jmp isr_common_stub

; Common ISR stub
isr_common_stub:
    pusha          ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds     ; Save data segment
    push eax

    mov ax, 0x10   ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx        ; Reload the original data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa           ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    add esp, 8     ; Clean up pushed error code and ISR number
    sti
    iret           ; Return from interrupt