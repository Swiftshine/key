#ifndef GFL_MEMORYUTIL_H
#define GFL_MEMORYUTIL_H

#include <stddef.h>
#include <string.h>

#include "gflMemoryManagement.h"
#include "gflAlloc.h"
#include "types.h"


#define GFL_ALLOC_WORK(dest, type) \
    type* temporary_pointer = new (gfl::HeapID::Work) type; \
    if (nullptr == temporary_pointer ) { delete dest; dest = nullptr; } else { dest = temporary_pointer ; }

namespace gfl {
    char* Strcpy(char* dst, size_t len, const char* src);
    inline char* Strcpy(const char* dst, size_t len, const char* src) {
        return Strcpy(const_cast<char*>(dst), len, src);
    }
    // void* Memcpy(void* dest, size_t len, void* src);
}
#endif
