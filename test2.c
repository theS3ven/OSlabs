#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <limits.h>

#define BLOCK_SIZE 64

typedef struct Block {
    struct Block* next;
}Block;

typedef struct Allocator {
    Block *Head;
    size_t size;
    size_t num_of_blocks;
    void *memory;
}Allocator;

Allocator* alloc_create(const size_t size, const void *memory) {
    Allocator *allocator = memory;
    
    allocator->memory = (void *)(((char *)memory) + sizeof(Block));

    allocator->num_of_blocks = (size - sizeof(Allocator)) / (BLOCK_SIZE + sizeof(Block));

    printf("Number of blocks: %d\n", allocator->num_of_blocks);

    Block* current_block = allocator->memory;

    allocator->Head = current_block;

    allocator->size = size - sizeof(Allocator);

    for(int i = 0; i < allocator->num_of_blocks; i++) {
        current_block->next = (Block *) ((char *)current_block + sizeof(Block) + BLOCK_SIZE);
        current_block = current_block->next;
    }

    current_block->next = NULL;

    return allocator;
}

int main() {
    size_t memory_size = 8192;
    void* memory = mmap(NULL, memory_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    Allocator* allocator = alloc_create(memory_size, memory);

    munmap(memory, memory_size);


    return 0;
}