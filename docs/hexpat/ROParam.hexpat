#pragma endian big
// NO PADDING OR ALIGNMENT!!!

import std.sys;
import std.mem;

struct String<auto N> {
    char mContents[N];
    padding[1]; // null terminator   
};

struct Array<T> {
    u32 mCount;
    T mContents[mCount];
};

enum BlockTag : u32 {
    BlockEnd    = 0x424C4B45, // BLKE
    BlockStart  = 0x424C4B53, // BLKS
};

struct ROObject<T> {
    BlockTag mStart;
    T mData;
    BlockTag mEnd;
};

struct MissionItem {
    String<4> mSignature1;
    u32 mMissionType;
    u32 mMissionIndex;
    String<4> mSignature2;
    u32 mROStringIndex;
    u32 mUnkInt1;
    String<4> mSignature3;
    u32 mUnkInts[2];
    u32 mUnkInt2;
    u32 mUnkInt3;
};

std::assert(sizeof(MissionItem) == 0x2F, "MissionItem mismatch!");

struct MissionROData {
    String<13> mName;
    Array<MissionItem> mMissionItems;
};

ROObject<MissionROData> missionRO @ 0xE2D8;
