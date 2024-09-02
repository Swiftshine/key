#ifndef GFL_MEMORYMANAGEMENT_H
#define GFL_MEMORYMANAGEMENT_H


#include <revolution/os.h>
#include "types.h"


namespace gfl {
    class Heap;

    ENUM_CLASS(HeapID,
        None        = 0,
        LIB1        = 1,
        LIB2        = 2,
        String      = 3,
        ETC         = 4,
        Sound       = 5,

        Work        = 10,
        Resource    = 11,
    );

    void* Alloc(u8 heapID, size_t size, uint align);
    void* Alloc(Heap* heap, size_t size, uint align);
    void Free(void*);
}


#endif