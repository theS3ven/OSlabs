#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <stddef.h>

typedef struct Allocator Allocator;

Allocator* allocator_create(void *memory, size_t size);
void allocator_destroy(Allocator *allocator);
void* allocator_alloc(Allocator *allocator, size_t size);
void allocator_free(Allocator *allocator, void *memory);

#endif // BUDDY_ALLOCATOR_H