#ifndef GFL_MEM_H
#define GFL_MEM_H

#include <types.h>
#include <MSL/internal/mem.h>

namespace gfl {
namespace mem {

    enum HeapID {
        None,
        Lib1,
        Lib2,
        String,
        Etc,
        Sound,
        Work,
        Resource,
    };
    
    void* alloc(u8 heapID, u32 size, int alignment);
    void  free(void* data);
    char* memcpy(char* dst, u32 len, char* src);
}
}
#endif
