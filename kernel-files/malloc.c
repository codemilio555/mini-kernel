#include "print.h"
#include "stdkernel.h"
#include "stdint.h"

#define MAX_HEAP 256

extern char _kernel_end[];

struct heapMemory
{
    int size;
    unsigned int is_free : 1;
    struct heapMemory *next;
};
void init_malloc()
{
    unsigned int heap_start = (unsigned int)&_kernel_end;
    struct heapMemory *start;
    start = (struct heapMemory *)heap_start;
    start->is_free = 0;
    start->size = 10;
    start->next = (struct heapMemory *)0;
}
void *malloc(int len)
{

    unsigned int heap_start = (unsigned int)&_kernel_end;

    int *heap = (int *)heap_start;
    // finding best spot
    int at = 0;
    int heap_addr = heap_start;

    struct heapMemory *start;
    struct heapMemory *best;
    best->size=0;
    while (1)
    {
        start = (struct heapMemory *)heap_addr;
        //It is the first malloc
        if(start->next==0){
            start->is_free=1;
            start->size=len;
            start->next=(struct heapMemory*)heap_addr+sizeof(struct heapMemory)+len;
            return (void*)heap_addr+sizeof(struct heapMemory);
            break;
        }
        if(start->is_free==0){
            //It if free, chacking if it is OK
            unsigned int size = start->size;
            //Simple, not fusing things
            //@TODO make it fusing
            if(size<len){
                continue;
            }

            //trying to find the best spot
            unsigned int diffBest = best->size - len;
            //unsigned int di

        }
        heap_addr=(int)start->next;

        if ((heap_addr - heap_start) >= MAX_HEAP)
        {
            // Out of Memory
            return NULL;
        }
    }
}

void free(void *var)
{
}