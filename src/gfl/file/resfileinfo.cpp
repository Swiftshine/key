#include <gfl/file/ResFileInfo.h>
#include <gfl/string/FixedString.h>

gfl::ResFileInfo::ResFileInfo() {
    flags = 0;
    level = 0;
    hash = 0;
    filename = NULL;
    entrynum = 0;
    archive = 0;
}

void gfl::ResFileInfo::Free(u8 heapID) { common_dtor(this, heapID); }


gfl::ResFileInfo* gfl::ResFileInfo::fn_8063E38C(const char* arg1, void* arg2, void* arg3) { return NULL; }

int gfl::ResArchivedFileInfo::Recurse() {
    if (child) { return child->Recurse(); }
    return 0;
}

gfl::GfArch* gfl::ResFileInfo::GetGfArch() {
    if (flags & ResInfo::Flags::GfArch) {
        return archive;
    }

    return NULL;
}


gfl::ResArchivedFileInfo::~ResArchivedFileInfo() {
    if (level) {
        delete child;
        child = NULL;
        data = NULL;
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
