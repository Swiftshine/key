#ifndef FLUFF_COLDATA_H
#define FLUFF_COLDATA_H

#include "types.h"
#include <utility>
#include <string>
#include "object/collision/Colbin.h"
#include "object/collision/KdTreeData.h"

/// @note Size: `0x20`
class ColData : public KdTreeData {
public:
    inline ColData* GetNext() {
        return mNext;
    }

    inline void SetNext(ColData* next) {
        mNext = next;
    }

    /* Class Members */

    /* 0x08 */ ColData* mNext;
    /* 0x0C */ uint m_C;
    /* 0x10 */ uint m_10;
    /* 0x14 */ uint mNumEntries;
    /* 0x18 */ uint m_18;
    /* 0x1C */ uint m_1C;
};

// size: 0x40
class ColDataSeg : public ColData {
public:
    ColDataSeg();
    DECL_WEAK virtual ~ColDataSeg();
private:
    u16 mIndex;
    u16 m_22;
    nw4r::math::VEC2 mStart;
    nw4r::math::VEC2 mEnd;
    nw4r::math::VEC2 mNormalizedVector;
    uint m_3C;
};

// size: 0x48
class ColDataSegLabel : public ColData {
public:
    ColDataSegLabel();
    virtual ~ColDataSegLabel();
};

#endif
