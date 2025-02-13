#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// IDT Gate Types
#define IDT_GATE_TASK      0x5
#define IDT_GATE_INT16     0x6
#define IDT_GATE_TRAP16    0x7
#define IDT_GATE_INT32     0xE
#define IDT_GATE_TRAP32    0xF

// IDT entry structure
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t base_high;
} __attribute__((packed));

// IDT pointer structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Function declarations
void init_idt(void);  // Changed from idt_init to init_idt
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

extern void idt_load(struct idt_ptr* idt_ptr_addr);

#endif
