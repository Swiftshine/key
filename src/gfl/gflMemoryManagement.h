#ifndef GFL_MEMORYMANAGEMENT_H
#define GFL_MEMORYMANAGEMENT_H

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

void* operator new(size_t size, u8 heapID);
inline void* operator new[](size_t size, u8 heapID) { return operator new(size, heapID); }
void operator delete(void* ptr);
inline void operator delete[](void* ptr) { operator delete(ptr); }

#endif