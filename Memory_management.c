#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct MemoryBlock {
    struct MemoryBlock *pnt; //pointer to part of memorybool in the memory
    struct MemoryBlock * Next; // pointer ton the next MemoryBlock
    int size; // size of the alocated memory
    bool free;  // if a piece of memory is free to alocate of not 
} MemoryBlock;




void* memory_pool = NULL;
MemoryBlock* Block = NULL;

