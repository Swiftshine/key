#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include <stddef.h>

void* operator new(size_t size, unsigned char heapID);
void  operator delete(void* ptr, unsigned char heapID);

#endif