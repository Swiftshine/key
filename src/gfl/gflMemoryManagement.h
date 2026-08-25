#ifndef GFL_MEMORYMANAGEMENT_H
#define GFL_MEMORYMANAGEMENT_H

#include "types.h"
#include <revolution/os.h>


namespace gfl {
    class Heap;

    enum HeapID {
        eHeapID_None        = 0,
        eHeapID_LIB1        = 1,
        eHeapID_LIB2        = 2,
        eHeapID_String      = 3,
        eHeapID_ETC         = 4,
        eHeapID_Sound       = 5,

        eHeapID_Work        = 10,
        eHeapID_Resource    = 11,
    };

    void* Alloc(u8 heapID, size_t size, u32 align);
    void* Alloc(Heap* heap, size_t size, u32 align);
    void Free(void*);
}


#endif
