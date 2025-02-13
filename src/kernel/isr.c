#include "isr.h"
#include "idt.h"

void isr_init(void) {
    // Install ISRs into the IDT
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
}

void isr_handler(struct registers* regs) {
    // Forward to interrupt handler if registered
    if (regs->int_no < 32) {
        // Handle CPU exceptions here
    }
}
