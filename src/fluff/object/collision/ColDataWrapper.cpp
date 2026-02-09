#include "object/collision/ColDataWrapper.h"
#include "gfl/gflMemoryUtil.h"
ColDataWrapper::ColDataWrapper(const ColDataWrapper* pOther)
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

    CreateColDataPoints(pOther->mNumPoints);
    CreateColDataSegs(pOther->mNumSegs);
    CreateColDataCircles(pOther->mNumCircles);
    CreateColDataRects(pOther->mNumRects);

    for (uint i = 0; i < mNumPoints; i++) {
        ColDataPoint* mine = &mColDataPoints[i];
        ColDataPoint* theirs = &pOther->mColDataPoints[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumSegs; i++) {
        ColDataSeg* mine = &mColDataSegs[i];
        ColDataSeg* theirs = &pOther->mColDataSegs[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumCircles; i++) {
        ColDataCircle* mine = &mColDataCircles[i];
        ColDataCircle* theirs = &pOther->mColDataCircles[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumRects; i++) {
        ColDataRect* mine = &mColDataRects[i];
        ColDataRect* theirs = &pOther->mColDataRects[i];
        mine->Copy(theirs);
    }
}

ColDataWrapper* ColDataWrapper::Copy(ColDataWrapper* pOther) {
    if (mColDataPoints == nullptr || mNumPoints != pOther->mNumPoints) {
        delete[] mColDataPoints;
        mColDataPoints = nullptr;
        CreateColDataPoints(pOther->mNumPoints);
    }

    if (mColDataSegs == nullptr || mNumSegs != pOther->mNumSegs) {
        delete[] mColDataSegs;
        mColDataSegs = nullptr;
        CreateColDataSegs(pOther->mNumSegs);
    }

    if (mColDataCircles == nullptr || mNumCircles != pOther->mNumCircles) {
        delete[] mColDataCircles;
        mColDataCircles = nullptr;
        CreateColDataCircles(pOther->mNumCircles);
    }

    if (mColDataRects == nullptr || mNumRects != pOther->mNumRects) {
        delete[] mColDataRects;
        mColDataRects = nullptr;
        CreateColDataRects(pOther->mNumRects);
    }

    for (uint i = 0; i < mNumPoints; i++) {
        ColDataPoint* mine = &mColDataPoints[i];
        ColDataPoint* theirs = &pOther->mColDataPoints[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumSegs; i++) {
        ColDataSeg* mine = &mColDataSegs[i];
        ColDataSeg* theirs = &pOther->mColDataSegs[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumCircles; i++) {
        ColDataCircle* mine = &mColDataCircles[i];
        ColDataCircle* theirs = &pOther->mColDataCircles[i];
        mine->Copy(theirs);
    }

    for (uint i = 0; i < mNumRects; i++) {
        ColDataRect* mine = &mColDataRects[i];
        ColDataRect* theirs = &pOther->mColDataRects[i];
        mine->Copy(theirs);
    }

    return this;
}

ColDataWrapper::~ColDataWrapper() {
    RemoveAll();
    delete[] mColDataPoints;
    delete[] mColDataSegs;
    delete[] mColDataCircles;
    delete[] mColDataRects;
}

void ColDataWrapper::CreateColDataPoints(uint count) {
    if (count == 0) {
        return;
    }

    mColDataPoints = new (gfl::HeapID::Work) ColDataPoint[count];
    mNumPoints = count;

    for (uint i = 0; i < count; i++) {
        mColDataPoints[i].mIdentity.mIndex = i;
    }
}

// https://decomp.me/scratch/weXoy
ColDataPoint::ColDataPoint()
    : ColData()
    , mIdentity()
    , mPosition(0.0f, 0.0f)
{ }

void ColDataWrapper::CreateColDataSegs(uint count) {
    if (count == 0) {
        return;
    }

    mColDataSegs = new (gfl::HeapID::Work) ColDataSeg[count];
    mNumSegs = count;

    for (uint i = 0; i < count; i++) {
        mColDataSegs[i].mIdentity.mIndex = i;
    }
}

void ColDataWrapper::CreateColDataCircles(uint count) {
    if (count == 0) {
        return;
    }

    mColDataCircles = new (gfl::HeapID::Work) ColDataCircle[count];
    mNumCircles = count;

    for (uint i = 0; i < count; i++) {
        mColDataCircles[i].mIdentity.mIndex = i;
    }
}

void ColDataWrapper::CreateColDataRects(uint count) {
    if (count == 0) {
        return;
    }

    mColDataRects = new (gfl::HeapID::Work) ColDataRect[count];
    mNumRects = count;

    for (uint i = 0; i < count; i++) {
        mColDataRects[i].mIdentity.mIndex = i;
    }
}
