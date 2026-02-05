#ifndef FLUFF_MNEB_H
#define FLUFF_MNEB_H

#include "gfl/gflResFileInfo.h"
#include "gfl/gflOffset.h"

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

    struct ControlPoint {
        s16 x, y, z, w;
    };

    struct KeyFrame {
        u16 mFrame;
        bool mActive;
        s16 mPosX;
        s16 mPosY;
    };

    struct KeyFrameSet {
        u16 mControlPointIndex;
        u16 mNumKeyFrames;
        KeyFrame mKeyFrames[];
    };

    struct KeyFrameSetTable {
        u32 mNumKeyFrameSets;
        gfl::Offset<KeyFrameSet> mKeyFrameSetOffsets[];
    };

    struct UnkStruct {
        // ?
    };

    struct UnkTable {
        u32 mUnkCount;
        gfl::Offset<UnkStruct> m_4[];
    };

    struct KeyFrameInfo {
        gfl::Offset<KeyFrameSetTable> mKeyFrameSetTableOffset;
        gfl::Offset<UnkTable> m_4;
        gfl::Offset<placeholder_t> m_8;
        gfl::Offset<placeholder_t> m_C;
    };

    struct CurveBlock {
        char mMagic[4];
        size_t mBlockSize;
        char mName[0x20];
        char m_28[100];
        float m_8C;
        u32 m_90;
        bool m_94;
        int m_98;
        gfl::Offset<ControlPoint> mControlPointOffset;
        gfl::Offset<float> mKnotOffset;
        gfl::Offset<KeyFrameInfo> mKeyFrameInfoOffset;
        float m_A8[4];

        /* additional data comes after this but it's not always part of this struct */
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
        gfl::Offset<DemoOption> mDemoOptions;
    };

    struct DemoDataBlock {
        char mMagic[4];
        size_t mBlockSize;
        uint mDemoOptionSetCount;
        gfl::Offset<DemoOptionSet> mDemoOptionSets;
    };


    class File {
    public:
        NURBSSet* Load(NURBSSet* pNURBSSet, const char* pFilepath);
        CurveBlock* GetNextCurveBlock(CurveBlock* pBlock) const;
        /// @return The number of curves in the file.
        uint CopyHeader(void* pData);
        void SetCurveBlock(NURBSObject* pObj, CurveBlock* pBlock);
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
