#ifndef FLUFF_COLDATAWRAPPER_H
#define FLUFF_COLDATAWRAPPER_H

#include "types.h"
#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"
#include "object/collision/ColData.h"

class ColObj;
class ColDataPoint;
class ColDataSeg;
class ColDataCircle;
class ColDataRect;

/// @note Size: `0x30`
class ColDataWrapper {
public:
    inline ColDataWrapper()
        : mBoundsMin(0.0f, 0.0f)
        , mBoundsMax(0.0f, 0.0f)
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
    ColDataPoint* GetColDataPoint(uint index) const;
    ColDataSeg* GetColDataSeg(uint index) const;
    ColDataCircle* GetColDataCircle(uint index) const;
    ColDataRect* GetColDataRect(uint index) const;
    ColData* GetColData(uint index) const;
    uint GetNumColData() const;
    void SetOwner(ColObjTrans* pColObj);
    void Update();
    void fn_800CFD14(/* args unk */);
    void NormalizeColDataSegs();
    void SetFlags(u64 flags);
    void AddFlags(u64 flags);
    void ClearFlags(u64 flags);
    u64 CalculateFlags() const;
    void fn_800D080C(bool arg1);
    void fn_800D0948(bool arg1);
    void AdjustBounds();
    void RemoveAll();
    void AddAll();
    void Add(ColObj* pColObj);

    /* Class Members  */

    uint mNumPoints;
    ColDataPoint* mColDataPoints;
    uint mNumSegs;
    ColDataSeg* mColDataSegs;
    uint mNumCircles;
    ColDataCircle* mColDataCircles;
    uint mNumRects;
    ColDataRect* mColDataRects;
    gfl::Vec2 mBoundsMin;
    gfl::Vec2 mBoundsMax;
};

struct ColDataIdentity {
    ColDataIdentity()
        : mIndex(0)
        , mEnableFlag(0)
    { }
    u16 mIndex;
    u16 mEnableFlag;
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
    ColDataCircle();
    virtual ~ColDataCircle();

    /* Class Members */
    ColDataIdentity mIdentity;
    gfl::Vec3 mInfo; // position (x, y), radius (z)
};

class ColDataRect : public ColData {
public:
    ColDataRect();
    virtual ~ColDataRect();

    ColDataIdentity mIdentity;
    gfl::Vec2 mBoundsMin;
    gfl::Vec2 mBoundsMax;
    u32 m_34;
};


#endif
