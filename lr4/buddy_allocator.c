#include "buddy_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define MIN_BLOCK_SIZE 64
#define MAX_ORDER 20

typedef struct Block {
    struct Block *next;
    size_t order;
} Block;

typedef struct Allocator {
    void *memory;
    size_t size;
    size_t order;
    struct Block *freelist[MAX_ORDER + 1];
} Allocator;

Allocator* allocator_create(void *memory, size_t size) {
    if (size < MIN_BLOCK_SIZE) return NULL;

    // Выделяем дополнительное место для структуры Allocator
    size_t alloc_size = sizeof(Allocator);
    if (size <= alloc_size) return NULL;

    Allocator *allocator = (Allocator *)memory;
    allocator->memory = mmap(NULL, size - alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (allocator->memory == MAP_FAILED) {
        return NULL;
    }

    allocator->size = size - alloc_size;
    allocator->order = 0;

    while ((1UL << allocator->order) < allocator->size) {
        allocator->order++;
    }

    // Инициализация списков свободных блоков
    for (size_t i = 0; i <= MAX_ORDER; i++) {
        allocator->freelist[i] = NULL;
    }

    // Создаём первый блок
    Block *block = (Block*)allocator->memory;
    block->next = NULL;
    block->order = allocator->order;
    allocator->freelist[allocator->order] = block;

    return allocator;
}

void allocator_destroy(Allocator *allocator) {
    if (!allocator) return;
    munmap(allocator->memory, allocator->size);
}

void* allocator_alloc(Allocator *allocator, size_t size) {
    if (!allocator || size == 0) return NULL;

    size_t order = 0;
    while ((1UL << order) < size + sizeof(Block)) { // Учитываем заголовок блока
        order++;
    }
    if (order > MAX_ORDER) return NULL;

    for (size_t i = order; i <= MAX_ORDER; i++) {
        if (allocator->freelist[i]) {
            Block *block = allocator->freelist[i];
            allocator->freelist[i] = block->next;

            while (i > order) {
                i--;
                Block *buddy = (Block*)((char*)block + (1UL << i));
                buddy->next = allocator->freelist[i];
                buddy->order = i;
                allocator->freelist[i] = buddy;
            }

            block->next = NULL;
            block->order = order;
            return (void*)((char*)block + sizeof(Block)); // Пропускаем заголовок
        }
    }
    return NULL;
}

void allocator_free(Allocator *allocator, void *ptr) {
    if (!allocator || !ptr) return;

    Block *block = (Block*)((char*)ptr - sizeof(Block));
    size_t order = block->order;

    while (order < allocator->order) {
        Block *buddy = (Block*)((char*)block + (1UL << order)); // Получаем адрес "бадди"

        // Проверяем, что бадди находится в свободном списке
        Block **prev = &allocator->freelist[order];
        Block *curr = allocator->freelist[order];
        while (curr) {
            if (curr == buddy && curr->order == order) {
                *prev = curr->next;
                block = (block < buddy) ? block : buddy; // Выбираем младший адрес
                order++;
                break;
            }
            prev = &curr->next;
            curr = curr->next;
        }
        if (!curr) break;
    }

    block->next = allocator->freelist[order];
    block->order = order;
    allocator->freelist[order] = block;
}