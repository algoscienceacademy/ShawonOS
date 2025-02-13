#ifndef SYSCALL_H
#define SYSCALL_H

#include <stddef.h>

#define SYS_WRITE 1
#define SYS_READ  2
#define SYS_EXIT  3

void init_syscalls(void);
int handle_syscall(int number, int arg1, int arg2, int arg3);

static int write_to_console(const char* str, size_t len);
static int read_from_console(char* buffer, size_t len);
static int terminate_process(int exit_code);

#endif
