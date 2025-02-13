#include "interrupt.h"
#include "idt.h"

static interrupt_handler_t handlers[256] = {0};

void interrupt_init(void) {
    // Set up default handlers for first 32 interrupts (CPU exceptions)
    for (int i = 0; i < 32; i++) {
        idt_set_gate(i, (uint32_t)default_interrupt_handler, 0x08, 0x8E);
    }
}

void set_interrupt_handler(uint8_t interrupt, interrupt_handler_t handler) {
    handlers[interrupt] = handler;
}

void interrupt_handler_main(uint32_t interrupt_number) {
    if (handlers[interrupt_number]) {
        handlers[interrupt_number]();
    }
}
