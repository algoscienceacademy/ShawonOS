#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Structure for registers
struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

// Function declarations
void isr_init(void);
void isr_handler(struct registers* regs);

// External assembly functions
extern void isr0(void);
extern void isr1(void);

#endif
