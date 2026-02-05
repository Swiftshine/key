#include "graphics/MNEB.h"
#include "graphics/NURBSSet.h"
#include "graphics/NURBSObject.h"

using namespace MNEB;

const char* MNDD_Magic = "MNDD";

NURBSSet* File::Load(NURBSSet* pNURBSSet, const char* pFilepath) {
    gfl::ResFileObject res = gfl::ResFileObject::FromArchive(pFilepath);

    CurveBlock* block;
    void* raw = res.GetData();

    if (raw == nullptr) {
        return nullptr;
    }

    mRawData = raw;
    size_t filesize = res.GetFilesize();
    u8* begin = (u8*)raw;
    u8* end = begin + filesize;
    uint count = CopyHeader(raw);
    pNURBSSet->Set(mNumFrames, count, mIsLooped, gfl::ResFileObject(res));

    block = (CurveBlock*)raw;
    for (uint i = 0; i < count; i++) {
        block = GetNextCurveBlock(block);
        NURBSObject* obj = pNURBSSet->GetObject(i);
        SetCurveBlock(obj, block);
    }

    for (u8* entry = (u8*)mRawData; (u8*)entry < end; entry = (u8*)GetNextCurveBlock((CurveBlock*)entry)) {
        // magic is checked twice?
        CheckMagic(MNDD_Magic, (EntryBase*)entry);

        if (CheckMagic(MNDD_Magic, (EntryBase*)entry)) {
            pNURBSSet->mEntry = GetDemoDataBlock(entry);
            break;
        }
    }

    return pNURBSSet;
}

CurveBlock* File::GetNextCurveBlock(CurveBlock* pBlock) const {
    return reinterpret_cast<CurveBlock*>(reinterpret_cast<u8*>(pBlock) + pBlock->mBlockSize);
}

uint File::CopyHeader(void* pData) {
    Header* header = reinterpret_cast<Header*>(pData);
    mFlags = header->mFlags;
    mIsLocked = header->mLock != LockState::Unlocked;
    header->mLock = LockState::Locked;
    mNumFrames = static_cast<float>(header->mNumFrames);
    mIsLooped = header->mIsLooped != 0 ? true : false;
    return header->mCurveBlockCount;
}

void File::SetCurveBlock(NURBSObject* pObj, CurveBlock* pBlock) {
    if (!mIsLocked) {

    }

    pObj->mCurveBlock = pBlock;
}

DemoDataBlock* File::GetDemoDataBlock(void* pData) {
    DemoDataBlock* block = reinterpret_cast<DemoDataBlock*>(pData);

    if (!mIsLocked) {
        for (uint i = 0; i < block->mDemoOptionSetCount; i++) {
            DemoOptionSet* curSet = &block->mDemoOptionSets[i];

            // block->mDemoOptionSets[i] = (DemoO((u32)curSet);
            DemoOptionSet* set = &block->mDemoOptionSets[i];
            for (uint j = 0; j < set->mNumDemoOptions; j++) {
                set[j].mDemoOptions = (DemoOption*) ((u8*)set->mDemoOptions + (size_t)mRawData);
            }
        }
    }

    return block;
}
