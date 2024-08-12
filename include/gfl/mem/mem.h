#ifndef GFL_MEM_H
#define GFL_MEM_H

#include <gfl/gfl_types.h>
#include <MSL/internal/mem.h>
#include <MSL/cstddef>
#include <revolution/types.h>
#include <gfl/mem/MemoryBase.h>

// void* operator new(size_t);
void* operator new(std::size_t size, u8);

inline void* operator new[](std::size_t size, u8 heapID) {
    return operator new(size, heapID);
}

namespace gfl {
namespace mem {

SCOPED_ENUM(HeapID,
    None = 0,
    LIB1 = 1,
    LIB2 = 2,
    String = 3,
    Etc = 4,
    Sound = 5,

    Work = 10,
    Resource = 11,
);

    
    void* Alloc(u8 heapID, u32 size, int alignment);
    void  Free(void* data);
    char* Memcpy(char* dst, u32 len, char* src);
    void  Delete(void* data, u8 heapID);
}
}

#endif
