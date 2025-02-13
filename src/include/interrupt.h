#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

// Interrupt handler function type
typedef void (*interrupt_handler_t)(void);

void interrupt_init(void);
void set_interrupt_handler(uint8_t interrupt, interrupt_handler_t handler);
void interrupt_handler_main(uint32_t interrupt_number);

// External assembly functions
extern void interrupt_handler_0(void);
extern void interrupt_handler_1(void);
extern void default_interrupt_handler(void);

#endif
