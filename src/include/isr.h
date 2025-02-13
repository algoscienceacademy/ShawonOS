#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// ISR handler function type
typedef void (*isr_t)(void);

// Structure for registers
struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

// External assembly functions
extern void isr0(void);
extern void isr1(void);
// Add more ISR declarations as needed...

// Function declarations
void isr_init(void);
void isr_handler(struct registers* regs);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
