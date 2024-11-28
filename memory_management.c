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
MemoryBlock* Block = NULL;





void mem_init(size_t size) {

    memory_pool = malloc(size);
    Block = malloc(sizeof(MemoryBlock));

    if (memory_pool == NULL || Block == NULL) {
        printf("memory_pool or Block was not allocated");
        return;
    }

    Block -> pnt = memory_pool;
    Block -> Next = NULL;
    Block -> size = size;
    Block -> free = true;


}





