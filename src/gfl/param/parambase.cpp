#include <gfl/param/ParamBase.h>
#include <gfl/mem/mem.h>
#include <decomp/thunks.h>
#include <string.h>

using namespace gfl;

Param::Param(const char* newLabel) {
    gfl::mem::Memcpy(this->label, sizeof(label), const_cast<char*>(newLabel));
    this->hash = ToHashInline(newLabel);
}

asm Param::~Param(void) {
    nofralloc
    b common_dtor
} 

bool Param::Matches(const char* compLabel, u32 compHash) {
    if (compHash != this->hash) {
        return false;
    }

    return strcmp(this->label, compLabel) == 0;
}

void Param::PrintRepeat(gfl::Console* console, u32 count) {
    for (u32 i = 0; i < count; i++) {
        console->Print("\t");
    }
}
