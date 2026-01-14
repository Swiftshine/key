#ifndef FLUFF_COLDATAWRAPPER_H
#define FLUFF_COLDATAWRAPPER_H

#include "types.h"
#include "gfl/gflVec2.h"

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
        mColDataPoints = nullptr;
        mNumSegs = 0;
        mColDataSegs = nullptr;
        mNumCircles = 0;
        mColDataCircles = nullptr;
        mNumRects = 0;
        mColDataRects = nullptr;
    }

    ~ColDataWrapper();

    void CreateColDataRects(uint count);
    void SetFlags(u64 flags);

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

#endif