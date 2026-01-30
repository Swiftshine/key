#pragma endian big

#include <std/string.pat>

struct Header {
    char mMagic[4]; // MNCH
    u32 mCurveEntryOffset;
    u32 mFlags;
    u32 mCurveEntryCount;
    u32 m_10;
    s16 m_14;
    bool m_16;
    padding[1];
};

struct ControlPoint {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
};

struct CurveBlock {
    u32 m_0;
    u32 m_4;
    s32 m_8;
    u32 mControlPointOffset;
    u32 mKnotOffset;
    u32 m_14;
    float m_18[8]; // transforms?
    u32 mNumControlPoints;
    ControlPoint mControlPoints[mNumControlPoints];
    u32 mNumKnots;
    float mKnots[mNumKnots];
    u32 m_unk_NextOffset;
    u8 m_unk_data[(m_unk_NextOffset - $)]; // anim data?
    u32 mUnk2;
    u32 mUnkArray2[mUnk2];
};


struct CurveEntry {
    char mMagic[4]; // MNCN
    u32 mEntrySize;
    char mName[0x20];
    u8 buf1[0x68];
    CurveBlock mCurveBlock;
};

Header header @ 0;
CurveEntry entries[header.mCurveEntryCount] @ header.mCurveEntryOffset;
