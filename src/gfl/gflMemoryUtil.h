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
    
    // this function:
    // - appends chars from `src` to `dst` while ensuring that the result is null-terminated
    // - always assigns 0 to `dst[len - 1]`
    char* Strncat(char* dst, size_t len, const char* src);
    inline char* Strncat(const char* dst, size_t len, const char* src) {
        return Strncat(const_cast<char*>(dst), len, src);
    }
}
#endif
