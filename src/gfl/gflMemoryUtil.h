#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include <stddef.h>
#include <string.h>

#include "gflMemoryManagement.h"
#include "gflAlloc.h"
#include "types.h"


#define GFL_ALLOC_WORK(dest, type) \
    type* temporary_pointer = new (gfl::HeapID::Work) type; \
    if (nullptr == temporary_pointer ) { delete dest; dest = nullptr; } else { dest = temporary_pointer ; }

namespace gfl {
    void* Memcpy(void* dest, size_t len, void* src);
}
#endif