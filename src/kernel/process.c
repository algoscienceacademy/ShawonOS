#include "process.h"
#include "memory.h"

#define MAX_PROCESSES 64

static process_t processes[MAX_PROCESSES];
static int current_process = 0;

void init_scheduler(void) {
    // Initialize process table
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].state = 2; // blocked
        processes[i].pid = i;
    }
}

int create_process(void (*entry_point)(void)) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == 2) { // Find a blocked slot
            processes[i].state = 0; // Set to ready
            processes[i].program_counter = (uint32_t)entry_point;
            processes[i].stack_pointer = (uint32_t)kmalloc(4096) + 4096; // 4KB stack
            processes[i].memory_space = NULL;
            return i;
        }
    }
    return -1; // No free process slots
}

void schedule(void) {
    if (++current_process >= MAX_PROCESSES) {
        current_process = 0;
    }
    
    // Find next ready process
    while (processes[current_process].state != 0) {
        if (++current_process >= MAX_PROCESSES) {
            current_process = 0;
        }
    }
}
