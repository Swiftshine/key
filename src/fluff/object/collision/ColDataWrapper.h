#ifndef FLUFF_COLDATAWRAPPER_H
#define FLUFF_COLDATAWRAPPER_H

#include "types.h"
#include "gfl/gflVec2.h"
#include "object/collision/ColData.h"

class ColDataPoint;
class ColDataSeg;
class ColDataCircle;
class ColDataRect;

/// @note Size: `0x30`
class ColDataWrapper {
public:
    inline ColDataWrapper()
        : m_20(0.0f, 0.0f)
        , m_28(0.0f, 0.0f)
    {
        mNumPoints = 0;
        mNumSegs = 0;
        mNumCircles = 0;
        mNumRects = 0;
        mColDataPoints = nullptr;
        mColDataSegs = nullptr;
        mColDataCircles = nullptr;
        mColDataRects = nullptr;
    }

    ColDataWrapper(const ColDataWrapper* pOther);
    ~ColDataWrapper();

    /* Class Methods */
    ColDataWrapper* Copy(ColDataWrapper* pOther);


    void CreateColDataPoints(uint count);
    void CreateColDataSegs(uint count);
    void CreateColDataCircles(uint count);
    void CreateColDataRects(uint count);

    void RemoveAll();

    void SetFlags(u64 flags);

    /* Class Members  */

    uint mNumPoints;
    ColDataPoint* mColDataPoints;
    uint mNumSegs;
    ColDataSeg* mColDataSegs;
    uint mNumCircles;
    ColDataCircle* mColDataCircles;
    uint mNumRects;
    ColDataRect* mColDataRects;
    gfl::Vec2 m_20;
    gfl::Vec2 m_28;
};

struct ColDataIdentity {
    ColDataIdentity()
        : mIndex(0)
        , m_2(0)
    { }
    u16 mIndex;
    u16 m_2;
};

/// @note Size: `0x30`
class ColDataPoint : public ColData {
public:
    ColDataPoint();
    virtual ~ColDataPoint();
    ColDataIdentity mIdentity;
    gfl::Vec2 mPosition;
    u32 m_2C;
};

// size: 0x40
class ColDataSeg : public ColData {
public:
    ColDataSeg();
    DECL_WEAK virtual ~ColDataSeg();

    /* Class Members */

    ColDataIdentity mIdentity;
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

class ColDataCircle : public ColData {
public:
    virtual ~ColDataCircle();

    /* Class Members */
    ColDataIdentity mIdentity;
    gfl::Vec2 m_24;
    u32 m_2C;
};

class ColDataRect : public ColData {
public:
    virtual ~ColDataRect();

    ColDataIdentity mIdentity;
    gfl::Vec2 mBoundsMin;
    gfl::Vec2 mBoundsMax;
    u32 m_34;
};


#endif
