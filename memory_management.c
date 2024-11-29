#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"

typedef struct MemoryBlock {
    void * pnt; //pointer to part of memorypool in the memory
    struct MemoryBlock * Next; // pointer ton the next MemoryBlock
    int size; // size of the alocated memory
    bool free;  // if a piece of memory is free to alocate of not 
} MemoryBlock;


void* memory_pool = NULL;
MemoryBlock* Block_pool = NULL; //name changed





void mem_init(size_t size) {

    memory_pool = malloc(size);
    Block_pool = malloc(sizeof(MemoryBlock));

    if (memory_pool == NULL || Block_pool == NULL) {
        printf("memory_pool or Block was not allocated");
        return;
    }

    Block_pool -> pnt = memory_pool;
    Block_pool -> Next = NULL;
    Block_pool -> size = size;
    Block_pool -> free = true;


}




void* mem_alloc(size_t size) {
    MemoryBlock* current = Block_pool;


    while (current != NULL) {
        
        if (current -> free = true && current -> size >= size) {

            MemoryBlock* New_block = malloc(sizeof(MemoryBlock));

            New_block -> pnt = current -> pnt + size;

            New_block -> Next = NULL;
            current -> Next = New_block;

            New_block -> size = current -> size - size;
            current -> size = size;

            New_block -> free = true;
            current -> free = false;


        } else {
            current = current -> Next;
        }

        return current -> pnt;

    }

    return NULL;

}
