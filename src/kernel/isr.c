#include "isr.h"
#include "idt.h"

static isr_t interrupt_handlers[256];

void isr_init(void) {
    // Set up ISR handlers in IDT
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);   // Division by zero
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);   // Debug
    // Initialize handlers array
    for (int i = 0; i < 256; i++) {
        interrupt_handlers[i] = 0;
    }
}

void isr_handler(struct registers* regs) {
    if (interrupt_handlers[regs->int_no] != 0) {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler();
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}
