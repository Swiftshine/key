#ifndef FLUFF_COLDATA_H
#define FLUFF_COLDATA_H

#include "types.h"
#include <utility>
#include <string>
#include "object/collision/Colbin.h"
#include "object/collision/KdTreeData.h"

// size: 0x20?
class ColData : public KdTreeData {
public:
    inline ColData* GetNext() {
        return mNext;
    }

    inline void SetNext(ColData* next) {
        mNext = next;
    }

protected:
    ColData* mNext; // @ 0x8
    uint m_C;
    uint m_10;
    uint mNumEntries; // @ 0x14
    uint m_18;
    uint m_1C;
};

// size: 0x40
class ColDataSeg : public ColData {
public:
    ColDataSeg();
    DECL_WEAK virtual ~ColDataSeg();

    void AddSelf();
    void RemoveSelf();
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
