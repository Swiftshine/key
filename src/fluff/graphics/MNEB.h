#ifndef FLUFF_MNEB_H
#define FLUFF_MNEB_H

#include "gfl/gflResFileInfo.h"

class NURBSSet;
class NURBSObject;

// Data Definition?
// sdata

namespace MNEB {
    ENUM_CLASS(LockState,
        Unlocked = 0,
        Locked = 1,
    );

    struct Header {
        char mMagic[4];
        u32 mCurveBlockOffset;
        u32 mFlags;
        uint mCurveBlockCount;
        u32 mLock;
        u16 mNumFrames;
        u8 mIsLooped;
    };

    struct EntryBase {
        char mMagic[4];
    };

    struct CurveBlock {
        char mMagic[4];
        size_t mBlockSize;
        // todo: fill this out properly
    };

    struct DemoOption {
        s16 GetOption(float);
        char mName[0x10];
        size_t mOptionLength;
        char mOption[];
    };

    struct DemoOptionSet {
        char mName[0x20];
        char m_20[0x20];
        uint mNumDemoOptions;
        DemoOption* mDemoOptions;
    };

    struct DemoDataBlock {
        char mMagic[4];
        size_t mBlockSize;
        uint mDemoOptionSetCount;
        DemoOptionSet* mDemoOptionSets;
    };


    class File {
    public:
        NURBSSet* Load(NURBSSet* pNURBSSet, const char* pFilepath);
        CurveBlock* GetNextCurveBlock(CurveBlock* pBlock) const;
        /// @return The number of curves in the file.
        uint CopyHeader(void* pData);
        void SetCurveBlock(NURBSObject* pObj, CurveBlock* pEntry);
        DemoDataBlock* GetDemoDataBlock(void* pData);

        bool CheckMagic(const char* pMagic, EntryBase* entry) {
            return (
                entry->mMagic[0] == pMagic[0] &&
                entry->mMagic[1] == pMagic[1] &&
                entry->mMagic[2] == pMagic[2] &&
                entry->mMagic[3] == pMagic[3]
            ) ? true : false;
        }

        /* Class Members */

        /* 0x00 */ uint mFlags;
        /* 0x04 */ bool mIsLocked;
        /* 0x08 */ float mNumFrames;
        /* 0x0C */ bool mIsLooped;
        /* 0x10 */ void* mRawData;
    };
}

#endif
