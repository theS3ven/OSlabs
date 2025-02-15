#include "mck_allocator.h"
#include <stddef.h>
#include <string.h>
#include <stdint.h>


#define MAX_CLASS 10
#define PAGE_SIZE 4096

typedef struct Block {
    struct Block *next;
} Block;

struct Allocator {
    Block* freelist[MAX_CLASS];
    size_t class_size[MAX_CLASS];
    void *memory;
    size_t size;
};

Allocator* allocator_create(void *memory, size_t size) {
    Allocator *allocator = (Allocator *)memory;
    if(size < sizeof(Allocator)){
        return NULL;
    }
    allocator->memory = (char*)memory + sizeof(Allocator);
    allocator->size = size - sizeof(Allocator);

    size_t block_size = 16;
    for(size_t i = 0; i < MAX_CLASS; i++){
        allocator->class_size[i] = block_size;
        allocator->freelist[i] = NULL;
        block_size *= 2;
    }

    return allocator;
}

void allocator_destroy(Allocator *allocator) {
    for(size_t i = 0; i < MAX_CLASS; i++){
        allocator->freelist[i] = NULL;
    }
}

static size_t find_class(size_t size, size_t* class_size, size_t num_classes){
    for(size_t i = 0; i < num_classes; i++){
        if(size <= class_size[i]){
            return i;
        }
    }
    return num_classes;
}

void* allocator_alloc(Allocator *allocator, size_t size) {
    size_t class_i = find_class(size, allocator->class_size, MAX_CLASS);
    if(class_i >= MAX_CLASS){
        return NULL;
    }

    Block* block = allocator->freelist[class_i];
    if(block){
        allocator->freelist[class_i];
        return (void*)block;
    }

    size_t block_size = allocator->class_size[class_i];
    if(allocator->size < block_size){
        return NULL;
    }

    void* memory = allocator->memory;
    allocator->memory = (char*)allocator->memory + block_size;
    allocator->size -= block_size;
    
    return memory; 
}

void allocator_free(Allocator *allocator, void *memory) {
    if (!memory) {
        return;
    }

    uintptr_t address = (uintptr_t)memory - (uintptr_t)allocator;
    if(address >= allocator->size){
        return;
    }

    size_t class_i = 0;
    size_t block_size = 0;
    for(; class_i < MAX_CLASS; class_i++){
        block_size = allocator->class_size[class_i];
        if((uintptr_t)memory % block_size == 0){
            break;
        }
    }

    if(class_i >= MAX_CLASS){
        return;
    }

    Block* block = (Block*)memory;
    block->next = allocator->freelist[class_i];
    allocator->freelist[class_i] = block; 
}