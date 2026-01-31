#include "graphics/MNEB.h"

using namespace MNEB;

// Data Definition?
// sdata
const char* MNDD_Magic;

// https://decomp.me/scratch/kKphG
NURBSSet* File::Load(NURBSSet* pNURBSSet, const char* pFilepath) {
    gfl::ResFileObject res = gfl::ResFileObject::FromArchive(pFilepath);

    void* raw = res.GetData();
    
    if (raw == nullptr) {
        return nullptr;
    }

    mRawData = raw;
    size_t filesize = res.GetFilesize();
    u8* begin = (u8*)((CurveEntry*)raw)->mMagic;
    uint count = CopyHeader(raw);
    pNURBSSet->Set(m_8, count, m_C, gfl::ResFileObject(res));

    for (uint i = 0; i < count; i++) {
        CurveEntry* entry = GetNextEntry((CurveEntry*)raw);
        NURBSObject* obj = pNURBSSet->GetObject(i);
        SetObjectData(obj, entry);
    }

    for (CurveEntry* entry = (CurveEntry*)mRawData; (u8*)entry < (u8*)begin + filesize; entry = GetNextEntry(entry)) {
        bool mndd = false;
        if (
            entry->mMagic[0] == MNDD_Magic[0] &&
            entry->mMagic[1] == MNDD_Magic[1] &&
            entry->mMagic[2] == MNDD_Magic[2] &&
            entry->mMagic[3] == MNDD_Magic[3]
        ) {
            mndd = true;
        }
        
        if (mndd) {
            pNURBSSet->mEntry = fn_80029ED8(entry);
        }
    }

    return pNURBSSet;
}
