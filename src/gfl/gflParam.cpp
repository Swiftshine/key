#include <cstring>

#include "gflParam.h"
#include "gflMemoryUtil.h"
#include "gflChecksum.h"

using namespace gfl;

Param::Param(const char* newLabel) {
    gfl::Memcpy(mLabel, sizeof(mLabel), (void*)newLabel);
    mChecksum = gfl::Checksum(newLabel);
}

Param::~Param() { }

bool Param::Matches(const char* queryLabel, uint queryChecksum) {
    bool ret;
    
    if (queryChecksum != mChecksum) {
        ret = false;
    } else {
        int compResult = strcmp(mLabel, queryLabel);
        ret = 0 == compResult;
    }

    return ret;
}

void Param::PrintTabs(Console* console, uint count) {
    for (uint i = 0; i < count; i++) {
        console->Print("\t");
    }
}