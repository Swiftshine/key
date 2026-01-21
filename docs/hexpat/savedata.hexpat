#pragma endian big

import std.sys;
import std.mem;

struct string4 {
    char s[4];
};

bitfield TreasureFlags {
    padding     : 29;
    bool treasure1 : 1;
    bool treasure2 : 1;
    bool treasure3 : 1;
};

// size: 0x24
struct StageInfo {
    u32 m_0;
    u32 m_4;
    u32 m_8;
    u32 m_C;
    u32 mBeadStreak;
    u32 m_14;
    u32 mHighestBeadCount;
    TreasureFlags mObtainedTreasureFlags;
    bool m_20;
    padding[3];
};

// size: 0x3884
struct SaveSlot {
    u32 mIndex; // 0x0
    u32 m_4; // 0x4
    u32 mBeadCount; // 0x8
    u32 m_C; // 0xC
    u32 m_10; // 0x10
    u32 m_14; // 0x14
    string4 mAreaSignature; // 0x18
    string4 mStageSignature; // 0x1C
    string4 mLevelExitSignature; // 0x20 // ?
    u32 m_24;
    u32 m_28;
    bool m_2C;
    padding[3];
    u32 m_30[15]; // 0x30; these are pointers
    StageInfo mStageInfo[51]; // 0x6C
    char blah[0x30EC];
};

// std::print("Size StageInfo: {:#x} bytes", sizeof(StageInfo));
std::assert(sizeof(SaveSlot) == 0x3884, "wrong size!");

SaveSlot slot[3] @ 0x14;