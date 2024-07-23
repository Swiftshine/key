#include <gfl/param/parambase.h>
#include <gfl/mem/mem.h>
#include <decomp/thunks.h>

using namespace gfl;

Param::Param(const char* newLabel) {
    gfl::mem::Memcpy(this->label, sizeof(label), const_cast<char*>(newLabel));
    this->hash = ToHashInline(newLabel);
}

asm Param::~Param(void) {
    nofralloc
    b common_dtor
} 
