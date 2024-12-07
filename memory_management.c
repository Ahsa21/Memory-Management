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
        printf("memory_pool or Block was not allocated\n");
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
        
        if (current -> free == true && current -> size >= size) {

            MemoryBlock* New_block = malloc(sizeof(MemoryBlock));

            if (New_block == NULL) {
                printf("No new block was allocated!\n");
                return NULL;
            }

            New_block -> pnt = current -> pnt + size;

            New_block -> Next = current -> Next;
            current -> Next = New_block;

            New_block -> size = current -> size - size;
            current -> size = size;

            New_block -> free = true;
            current -> free = false;
            return current -> pnt;


        } else {
            current = current -> Next;
        }

    }

    return NULL;

}



void mem_free(void* block) {
    if (!block) {
        printf("You want to free a null pointer\n");
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
                free(Next_Block);
                }
                return;

        } else {
            current = current ->Next;
        }
    }
    
    
}


void* mem_resize(void* block, size_t size) {
    if (block ==NULL) {
        printf("It is not possible to resize a block that is NULL\n");

    } else {
        MemoryBlock* current = Block_pool;

        while(current != NULL) {
            if(current->pnt != block) {
                current = current ->Next;

            }
            
            else {

                if (current ->size >= size) {
                    printf("No need to resize\n");
                    return block;
                } else {
                    void* new_pointer = mem_alloc(size);
                    memcpy(new_pointer, block, current ->size);
                    mem_free(block);
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
    while (current != NULL) {
        MemoryBlock *Next_Block = current->Next;
        free(current);
        current = Next_Block;
    }

    Block_pool = NULL;

}