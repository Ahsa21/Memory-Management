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



void mem_free(void* block) {
    if (!block) {
        printf("You want to free a null pointer");
        return;
    }

    MemoryBlock * current = Block_pool;

    while (current != NULL) 
    {
        if (current ->pnt == block) {
            current ->free = true;

        MemoryBlock* Next_Block = current ->Next;
        if (current ->free && Next_Block !=NULL && Next_Block ->free) {
            current -> size += Next_Block -> size;
            current -> Next = Next_Block -> Next;
            }

        } else {
            current = current ->Next;
        }
    }

    return;
    
    
}


void* mem_resize(void* block, size_t size) {
    if (block ==NULL) {
        printf("It is not possible to resize a block that is NULL");

    } else {
        MemoryBlock* current = Block_pool;

        while(current != NULL) {
            if(current->pnt != block) {
                current = current ->Next;

            }
            
            else {

                if (current ->size >= size) {
                    printf("No need to resize");
                    return block;
                } else {
                    void* new_pointer = mem_alloc(size);
                    memcpy(new_pointer, block, current ->size);
                    return new_pointer;
                }
            }
        }
    }
}




void mem_deinit() {
    free(memory_pool);
    memory_pool = NULL;

    MemoryBlock*  current = Block_pool;
    while (current == NULL) {
        MemoryBlock* Next_Block = current;
         free(current);
         MemoryBlock* current = Next_Block ->Next;
    }

    Block_pool = NULL;

}