#include <gfl/file/ResFileInfo.h>
#include <gfl/string/FixedString.h>

gfl::ResFileInfo::ResFileInfo() {
    mFlags = 0;
    mLevel = 0;
    mHash = 0;
    mpFilename = NULL;
    mEntrynum = 0;
    mpArchive = 0;
}

void gfl::ResFileInfo::Free(u8 heapID) { common_dtor(this, heapID); }


gfl::ResFileInfo* gfl::ResFileInfo::fn_8063E38C(const char* arg1, void* arg2, void* arg3) { return NULL; }

int gfl::ResArchivedFileInfo::Recurse() {
    if (mpChild) { return mpChild->Recurse(); }
    return 0;
}

gfl::GfArch* gfl::ResFileInfo::GetGfArch() {
    if (mFlags & ResInfo::Flags::GfArch) {
        return mpArchive;
    }

    return NULL;
}


gfl::ResArchivedFileInfo::~ResArchivedFileInfo() {
    if (mLevel) {
        delete mpChild;
        mpChild = NULL;
        mpData = NULL;
    }
}

u32 gfl::ResArchivedFileInfo::GetDataSize() { return fn_807A43D0(this); }

void* gfl::ResArchivedFileInfo::GetData_thunk() { return GetData(); }
// gfl::ResFileInfo::~ResFileInfo() { }


// gfl::ResFileInfo* gfl::ResFileInfo::Get(const char* name, bool isFolder) {
//     ResFileInfo* result;
//     // FixedString nameFixed;

    
//     nameFixed = name;

//     return result;
// }
