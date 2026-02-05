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

// https://decomp.me/scratch/8Tfuy
void File::SetCurveBlock(NURBSObject* pObj, CurveBlock* pBlock) {
    if (!mIsLocked) {
        pBlock->mControlPointOffset.SetPointer(mRawData);
        pBlock->mKnotOffset.SetPointer(mRawData);
        KeyFrameInfo* kfi = pBlock->mKeyFrameInfoOffset.SetPointer(mRawData);

        if (kfi->mKeyFrameSetTableOffset.offset() != 0) {
            kfi->mKeyFrameSetTableOffset.SetPointer(mRawData);

            for (uint i = 0; i < kfi->mKeyFrameSetTableOffset->mNumKeyFrameSets; i++) {
                kfi->mKeyFrameSetTableOffset->mKeyFrameSetOffsets[i].SetPointer(mRawData);
            }
        }

        if (kfi->m_4.offset() != 0) {
            kfi->m_4.SetPointer(mRawData);

            for (uint i = 0; i < kfi->m_4->mUnkCount; i++) {
                kfi->m_4->m_4[i].SetPointer(mRawData);
            }
        }

        if (kfi->m_8.offset() != 0) {
            kfi->m_8.SetPointer(mRawData);
        }

        if (kfi->m_C.offset() != 0) {
            kfi->m_C.SetPointer(mRawData);
        }
    }

    pObj->mCurveBlock = pBlock;
}

DemoDataBlock* File::GetDemoDataBlock(void* pData) {
    if (!mIsLocked) {
        DemoDataBlock* block = reinterpret_cast<DemoDataBlock*>(pData);
        DemoOptionSet* p;
        DemoOptionSet* p1;
        for (uint i = 0; i < reinterpret_cast<DemoDataBlock*>(pData)->mDemoOptionSetCount; i++) {
            block->mDemoOptionSets.SetPointer(mRawData);
            p = block->mDemoOptionSets.pointer();
            p1 = block->mDemoOptionSets.pointer();

            for (uint j = 0; j < p->mNumDemoOptions; j++) {
                p1->mDemoOptions.SetPointer(mRawData);
                p1 = reinterpret_cast<DemoOptionSet*>((char*)p1 + 4);
            }

            block = reinterpret_cast<DemoDataBlock*>((char*)block + 4);
        }
    }

    return reinterpret_cast<DemoDataBlock*>(pData);
}
