#ifndef FLUFF_SAVEDATA_H
#define FLUFF_SAVEDATA_H

#define STAGE_COUNT     51
#define NUM_SAVE_SLOTS  3

#include "types.h"

enum ObtainedTreasureFlags {
    eObtainedTreasure_Treasure1 = 1 << 0,
    eObtainedTreasure_Treasure2 = 1 << 1,
    eObtainedTreasure_Treasure3 = 1 << 2,
};

/// @note Size: `0x24`
struct SaveData_StageInfo {
    s32 m_0;
    s32 m_4;
    s32 m_8;
    s32 m_C;
    s32 mBeadStreak;
    s32 m_14;
    s32 mHighestBeadCount;
    u32 mObtainedTreasureFlags;
    bool m_20; // maybe an indicator of whether or not the stage is completed?
};

/// @note Size: `0x3884`
class SaveSlot {
public:
    void fn_801FFDB8(u32 id);

    /* 0x0000 */ u32 mIndex;
    /* 0x0004 */ u32 mPlaytime; // in ticks; 1 tick * 60 = 1 second
    /* 0x0008 */ u32 mBeadCount;
    /* 0x000C */ u32 m_C;
    /* 0x0010 */ u32 m_10;
    /* 0x0014 */ u32 m_14;
    /* 0x0018 */ u32 mAreaSignature;
    /* 0x001C */ u32 mStageSignature;
    /* 0x0020 */ u32 mStageExitSignature; // as in, the stage that was *just* exited
    /* 0x0024 */ s32 mMissionID;
    /* 0x0028 */ s32 m_28;
    /* 0x002C */ bool m_2C;
    /* 0x0030 */ void* m_30[15];
    /* 0x006C */ SaveData_StageInfo mStageInfo[STAGE_COUNT];

    STRUCT_FILL(0x3884 - 0x798);
};

struct SaveData_Header {
    u32 mRegionCode;
    u32 mVersion;
    u32 mChecksum;
    u32 m_C;
    u32 m_10;
};

/// @note Size: `0xA9D4`
class SaveData {
public:
    /* Class Methods */

    u32 CalculateChecksum(s32 numBytes);
    void Init();
    BOOL IsValid(s32 numBytes);
    void InitSaveSlots();
    bool IsSizeValid(s32 size);
    bool IsChecksumValid();

    /* Class Members */

    /* 0x0000 */ SaveData_Header mHeader;
    /* 0x0014 */ SaveSlot mSaveSlots[NUM_SAVE_SLOTS];
    /* 0xA9A0 */ u32 m_A9A0;
    /* 0xA9A4 */ char mParameter[0x30]; // ?
};

#endif
