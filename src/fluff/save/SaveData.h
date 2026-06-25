#ifndef FLUFF_SAVEDATA_H
#define FLUFF_SAVEDATA_H

#define STAGE_COUNT     51
#define NUM_SAVE_SLOTS  3

#include "types.h"

ENUM_CLASS(ObtainedTreasureFlags,
    Treasure1 = 1 << 0,
    Treasure2 = 1 << 1,
    Treasure3 = 1 << 2,
);

/// @note Size: `0x24`
struct SaveData_StageInfo {
    int m_0;
    int m_4;
    int m_8;
    int m_C;
    int mBeadStreak;
    int m_14;
    int mHighestBeadCount;
    uint mObtainedTreasureFlags;
    bool m_20; // maybe an indicator of whether or not the stage is completed?
};

/// @note Size: `0x3884`
class SaveSlot {
public:
    void fn_801FFDB8(uint id);

    /* 0x0000 */ uint mIndex;
    /* 0x0004 */ uint m_4;
    /* 0x0008 */ uint mBeadCount;
    /* 0x000C */ uint m_C;
    /* 0x0010 */ uint m_10;
    /* 0x0014 */ uint m_14;
    /* 0x0018 */ uint mAreaSignature;
    /* 0x001C */ uint mStageSignature;
    /* 0x0020 */ uint mStageExitSignature; // as in, the stage that was *just* exited
    /* 0x0024 */ int mMissionID;
    /* 0x0028 */ int m_28;
    /* 0x002C */ bool m_2C;
    /* 0x0030 */ void* m_30[15];
    /* 0x006C */ SaveData_StageInfo mStageInfo[STAGE_COUNT];

    STRUCT_FILL(0x3884);
};

struct SaveData_Header {
    uint mRegionCode;
    uint mVersion;
    uint mChecksum;
    uint m_C;
    uint m_10;
};

/// @note Size: `0xA9D4`
class SaveData {
public:
    /* Class Methods */

    uint CalculateChecksum(int numBytes);
    void Init();
    BOOL IsValid(int numBytes);
    void InitSaveSlots();
    bool IsSizeValid(int size);
    bool IsChecksumValid();
    
    /* Class Members */

    /* 0x0000 */ SaveData_Header mHeader;
    /* 0x0014 */ SaveSlot mSaveSlots[NUM_SAVE_SLOTS];
    /* 0xA9A0 */ uint m_A9A0;
    /* 0xA9A4 */ char mParameter[0x30]; // ?
};

#endif
