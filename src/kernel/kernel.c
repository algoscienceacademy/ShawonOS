#include <stddef.h>
#include <stdint.h>
#include "memory.h"
#include "process.h"
#include "syscall.h"

void kernel_main(void) {
    // Initialize subsystems
    init_memory_manager();
    init_scheduler();
    init_syscalls();

    // Display welcome message
    const char *str = "Welcome to ShawonOS!";
    volatile uint16_t *video_memory = (uint16_t*)0xB8000;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        video_memory[i] = (uint16_t)str[i] | (uint16_t)(0x0F << 8);
    }

    while(1) {
        asm("hlt");
    }
}
