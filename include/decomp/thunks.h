#ifndef DECOMP_THUNKS_H
#define DECOMP_THUNKS_H


#include <types.h>

// MTX34 ctor
void fn_8066E8A0(void*);

// returns *(r3 + 0x6C)
bool fn_8078A5A0(void*);

// returns 0
int fn_806B1E40();

// returns 1
int fn_806FFEB0();

void common_dtor(void*,u8 heapID);

// gfl::Vec3 ctor
Vec3f fn_800127dc();

// returns *(r3 + 0x14)
u32 fn_807A43D0(void*);
#endif
