#ifndef GFL_ALLOC_H
#define GFL_ALLOC_H

#include "gflMemoryManagement.h"

void* operator new(size_t size, u8 heapID);
inline void* operator new[](size_t size, u8 heapID) { return operator new(size, heapID); }
void operator delete(void* ptr);
inline void operator delete[](void* ptr) { operator delete(ptr); }

#endif