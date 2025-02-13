#ifndef SYSCALL_H
#define SYSCALL_H

#include <stddef.h>

// System call numbers
#define SYS_WRITE 1
#define SYS_READ 2
#define SYS_EXIT 3

// System call function declarations
void init_syscalls(void);
int write_to_console(const char* str, size_t len);
int read_from_console(char* buffer, size_t len);
int terminate_process(int exit_code);

#endif
