#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include <stddef.h>
#include <string.h>
#include "types.h"


void* operator new(size_t size, u8 heapID);
void* operator new[](size_t size, u8 heapID);

namespace gfl {
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
    void Free(void* data);
    void* Memcpy(void* dest, size_t len, void* src);
}
#endif