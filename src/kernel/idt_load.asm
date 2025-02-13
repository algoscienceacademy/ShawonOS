; filepath: /Users/shahrearhossain/Documents/OS/ShawonOS/src/kernel/idt_load.asm
section .text
global idt_load

; void idt_load(struct idt_ptr* idt_ptr_addr);
idt_load:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]    ; Get the pointer to the IDT
    lidt [eax]            ; Load the IDT pointer
    pop ebp
    ret