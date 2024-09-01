#include <cstring>

#include "gflParam.h"
#include "gflMemoryUtil.h"
#include "gflChecksum.h"

using namespace gfl;

// String Array

ParamStrA::ParamStrA(const char* newLabel, uint count)
    : Param(newLabel)
    , mArray(nullptr)
    , mCount(count)
{
    mArray = new (gfl::HeapID::LIB1) std::string[mCount];
}

ParamStrA::~ParamStrA() {
    delete[] mArray;
}

int ParamStrA::vf8() {
    return 0;
}

void ParamStrA::vfC() {
    return;
}

void ParamStrA::Print(Console* console, uint numTabs) {
    PrintTabs(console, numTabs);
    
    console->Print("str[]  %-20s= {\n", mLabel);

    for (uint i = 0; i < mCount; i++) {
        PrintTabs(console, numTabs + 1);
        const char* str = mArray[i].begin();
        console->Print("\"%s\",\n", str);
    }

    PrintTabs(console, numTabs);
    console->Print("} ");
    console->Print("\t#%s\n", 0);
    console->Print("\n");
}

// Base Class

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