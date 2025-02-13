#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

typedef struct {
    uint32_t pid;
    uint32_t stack_pointer;
    uint32_t program_counter;
    void* memory_space;
    int state;  // 0=ready, 1=running, 2=blocked
} process_t;

void init_scheduler(void);
int create_process(void (*entry_point)(void));
void schedule(void);

#endif
