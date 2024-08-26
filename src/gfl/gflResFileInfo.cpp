#include "gflResFileInfo.h"
#include "gflFixedString.h"

using namespace gfl;

ResFileInfo::ResFileInfo() {
    mFlags = 0;
    mLevel = 0;
    mHash = 0;
    mFilename = nullptr;
    mEntrynum = 0;
    mArchive = 0;
}

// ResFileInfo::~ResFileInfo() { }

ResFileInfo* gfl::ResFileInfo::fn_8063E38C(const char* arg1, void* arg2, void* arg3) { return nullptr; }

int gfl::ResArchivedFileInfo::Recurse() {
    if (mChild) { return mChild->Recurse(); }
    return 0;
}

GfArch* gfl::ResFileInfo::GetGfArch() {
    if (mFlags & ResInfo::Flags::GfArch) {
        return mArchive;
    }

    return NULL;
}

ResArchivedFileInfo::~ResArchivedFileInfo() {
    if (mLevel) {
        delete mChild;
        mChild = nullptr;
        mData = nullptr;
    }
}

uint gfl::ResArchivedFileInfo::GetDataSize() { return mSize; }

void* gfl::ResArchivedFileInfo::GetData_thunk() { return GetData(); }