#include "print.h"
#include "stdkernel.h"
#include "stdint.h"

int first_malloc = 0;
#define MAX_HEAP 256

extern char _kernel_end[];

struct heapMemory
{
    int size;
    unsigned int is_free : 1;
    struct heapMemory *next;
};
void dump_heap() 
{
    unsigned int heap_start = (unsigned int)&_kernel_end;
    unsigned int heap_addr = heap_start;
    struct heapMemory *current;
    
    char buff[100]; // Puffer für deine itoa-Funktion
    
    print("\n--- HEAP DUMP START ---\n");
    
    print("[INFO] size of heapMemory: ");
    itoa(sizeof(struct heapMemory),buff);
    print(buff);
    print("\n");
    while (1) 
    {
        // 1. Sicherheitsnetz gegen Überlauf
        if (heap_addr - heap_start >= MAX_HEAP) {
            print("[DUMP] MAX_HEAP erreicht.\n");
            break;
        }

        current = (struct heapMemory *)heap_addr;

        // 2. Adresse des aktuellen Blocks ausgeben (als Dezimalzahl)
        print("Block bei Adresse: ");
        itoa(heap_addr, buff); 
        print(buff);

        // 3. Status des Blocks ausgeben
        print(" | Status: ");
        if (current->is_free == 1) {
            print("BELEGT (1)");
        } else if (current->is_free == 0) {
            print("FREI (0)");
        } else {
            print("KORRUPT (");
            itoa(current->is_free, buff);
            print(buff);
            print(")");
        }

        // 4. Größe ausgeben
        print(" | Groesse: ");
        itoa(current->size, buff);
        print(buff);

        // 5. Nächsten Pointer ausgeben
        print(" | Next: ");
        itoa((unsigned int)current->next, buff);
        print(buff);
        print("\n");

        // 6. Abbruchkriterien prüfen (nach deinen Regeln)
        if (current->next == 0) {
            print("[DUMP] Ende erreicht (Next ist 0).\n");
            break;
        }
        if ((int)current->next == 1) {
            print("[DUMP] Ende erreicht (Next ist 1 - Uninitialisiert).\n");
            break;
        }
        print("\nInhalt: ");
        unsigned int at =((int)current)+sizeof(struct heapMemory);
        char *value = (char*)at;
        print(value);
        print("\n");
        // 7. Weiterspringen zum nächsten Header
        heap_addr = (unsigned int)current->next;
    }

    print("--- HEAP DUMP END ---\n");
}



void *malloc(int len)
{
    
    unsigned int heap_start = (unsigned int)&_kernel_end;

    unsigned int *heap = (unsigned int *)heap_start;
    // finding best spot
    int at = 0;
    int heap_addr = heap_start;

    struct heapMemory *start;
    struct heapMemory bestStack;
    bestStack.size=0;
    struct heapMemory *best = &bestStack;
    while (1)
    {
        start = (struct heapMemory *)heap_addr;
        // last thing
        if (heap_addr - heap_start >= MAX_HEAP)
        {
            break;
        }

        // It is the first malloc
        if (first_malloc==0)
        {
            start->is_free = 1;
            start->size = len;
            start->next = (struct heapMemory *)(heap_addr + sizeof(struct heapMemory) + len);
            struct heapMemory *next = start->next;
            next->is_free = 0;
            first_malloc=1;
            best=start;
            //return (void *)heap_addr + sizeof(struct heapMemory);
            break;
        }
        if (start->is_free == 0)
        {
            // It if free, checking if it is OK
            unsigned int size = start->size;
            // Simple, not fusing things
            //@TODO make it fusing
            if (size < len)
            {
                goto next;
            }

            // trying to find the best spot
            unsigned int diffBest = best->size - len;
            unsigned int diffNow = size - len;

            if (diffBest < diffNow)
            {
                // best is better
                goto next;
            }
            // new is best
            best = start;
        }
    next:
        heap_addr = (int)start->next;
    }

    if (best->size == 0)
    {
        // best was never changed, we are out of memory!
        return NULL;
    }
    //if block is very big, spilt it
    if(best->size-len>sizeof(struct heapMemory)){
        unsigned int thisStart = (int)best + len+sizeof(struct heapMemory);
        struct heapMemory* next = (struct heapMemory*)thisStart;
        next->is_free=0;
        next->next=best->next;
        next->size=(int)next->next-(int)next;

        best->next=next;
    }

    best->is_free = 1;
    best->size = len;
    //best->next = (struct heapMemory *)best + sizeof(struct heapMemory) + len;
    return (void*)((int)best)+sizeof(struct heapMemory);
}

void free(void *var)
{
    unsigned int varHeap = (int)var - sizeof(struct heapMemory);
    struct heapMemory *varData = (struct heapMemory *)varHeap;
    struct heapMemory *next = (struct heapMemory*) varData->next;
    
    char buf[50];
    itoa(next->size,buf);
    if (next->is_free == 0)
    {
        varData->next=next->next;
        varData->size=varData->size+sizeof(struct heapMemory)+next->size;
    }
    varData->is_free=0;
}