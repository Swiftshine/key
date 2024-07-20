#ifndef GFL_MEM_H
#define GFL_MEM_H

#include <MSL/internal/mem.h>
#include <MSL/cstddef>
#include <revolution/types.h>

void* operator new(std::size_t);
inline void* operator new(std::size_t, u8);

namespace gfl {
namespace mem {

namespace HeapID {
    enum Enum_HeapID {
        None,
        LIB1,
        LIB2,
        String,
        Etc,
        Sound,
        Work,
        Resource,
    };
}
    
    void* Alloc(u8 heapID, u32 size, int alignment);
    void  Free(void* data);
    char* Memcpy(char* dst, u32 len, char* src);
    void  Delete(void* data, u8 heapID);
}
}

#endif
