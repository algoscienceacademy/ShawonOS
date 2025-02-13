#include "memory.h"

#define HEAP_START 0x100000
#define HEAP_SIZE  0x100000

typedef struct memory_block {
    size_t size;
    int is_free;
    struct memory_block* next;
} memory_block_t;

static memory_block_t* heap_start = (memory_block_t*)HEAP_START;

void init_memory_manager(void) {
    heap_start->size = HEAP_SIZE - sizeof(memory_block_t);
    heap_start->is_free = 1;
    heap_start->next = NULL;
}

void* kmalloc(size_t size) {
    memory_block_t* current = heap_start;
    while (current) {
        if (current->is_free && current->size >= size) {
            current->is_free = 0;
            return (void*)(current + 1);
        }
        current = current->next;
    }
    return NULL;
}

void kfree(void* ptr) {
    if (!ptr) return;
    memory_block_t* block = ((memory_block_t*)ptr) - 1;
    block->is_free = 1;
}
