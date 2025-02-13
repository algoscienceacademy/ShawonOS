#include "syscall.h"
#include <stdint.h>
#include <stddef.h>

static int write_to_console(const char* str, size_t len);
static int read_from_console(char* buffer, size_t len);
static int terminate_process(int exit_code);

void init_syscalls(void) {
    // Initialize system call handlers
}

int handle_syscall(int number, int arg1, int arg2, int arg3) {
    (void)arg3; // Suppress unused parameter warning
    switch(number) {
        case SYS_WRITE:
            return write_to_console((const char*)arg1, (size_t)arg2);
        case SYS_READ:
            return read_from_console((char*)arg1, (size_t)arg2);
        case SYS_EXIT:
            return terminate_process(arg1);
        default:
            return -1;
    }
}

static int write_to_console(const char* str, size_t len) {
    volatile uint16_t* video_mem = (uint16_t*)0xB8000;
    size_t i;
    for (i = 0; i < len && str[i]; i++) {
        video_mem[i] = (uint16_t)str[i] | (uint16_t)(0x0F << 8);
    }
    return (int)i;
}

static int read_from_console(char* buffer, size_t len) {
    (void)buffer; // Suppress unused parameter warning
    (void)len;    // Suppress unused parameter warning
    // Basic implementation - return 0 for now
    return 0;
}

static int terminate_process(int exit_code) {
    // Basic implementation - return exit code
    return exit_code;
}
