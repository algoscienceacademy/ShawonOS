#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void init_memory_manager(void);
void* kmalloc(size_t size);
void kfree(void* ptr);
void* get_physical_addr(void* virtual_addr);

#endif
