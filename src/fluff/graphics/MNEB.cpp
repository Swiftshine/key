#include "graphics/MNEB.h"
#include "graphics/NURBSSet.h"

using namespace MNEB;

// char MNEB::MNDD_Magic[] = "MNDD";

const char* MNDD_Magic;

NURBSSet* File::Load(NURBSSet* pNURBSSet, const char* pFilepath) {
    gfl::ResFileObject res = gfl::ResFileObject::FromArchive(pFilepath);

    CurveEntry* entry;
    void* raw = res.GetData();
    
    if (raw == nullptr) {
        return nullptr;
    }

    mRawData = raw;
    size_t filesize = res.GetFilesize();
    u8* begin = (u8*)raw;
    u8* end = begin + filesize;
    uint count = CopyHeader(raw);
    pNURBSSet->Set(m_8, count, m_C, gfl::ResFileObject(res));

    entry = (CurveEntry*)raw;
    for (uint i = 0; i < count; i++) {
        entry = GetNextEntry(entry);
        NURBSObject* obj = pNURBSSet->GetObject(i);
        SetObjectData(obj, entry);
    }

    for (u8* entry = (u8*)mRawData; (u8*)entry < end; entry = (u8*)GetNextEntry((CurveEntry*)entry)) {
        // magic is checked twice?
        CheckMagic(MNDD_Magic, (EntryBase*)entry);

        if (CheckMagic(MNDD_Magic, (EntryBase*)entry)) {
            pNURBSSet->mEntry = fn_80029ED8((MNDDEntry*)entry);
            break;
        }
    }

    return pNURBSSet;
}
