#include "object/collision/ColDataWrapper.h"
#include "gfl/gflMemoryUtil.h"
#include "object/collision/ColData.h"
#include "object/collision/ColObj.h"

ColDataWrapper::ColDataWrapper(const ColDataWrapper* pOther)
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

// unmatching due to ColData
ColDataCircle::ColDataCircle()
    : ColData()
    , mIdentity()
    , mInfo(0.0f)
{ }

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

// unmatching due to ColData
ColDataRect::ColDataRect()
    : ColData()
    , mIdentity()
    , mBoundsMin(0.0f, 0.0f)
    , mBoundsMax(0.0f, 0.0f)
    , m_34(0)
{ }

ColDataPoint* ColDataWrapper::GetColDataPoint(uint index) const {
    return mColDataPoints + index;
}

ColDataSeg* ColDataWrapper::GetColDataSeg(uint index) const {
    return mColDataSegs + index;
}

ColDataCircle* ColDataWrapper::GetColDataCircle(uint index) const {
    return mColDataCircles + index;
}

ColDataRect* ColDataWrapper::GetColDataRect(uint index) const {
    return mColDataRects + index;
}

// https://decomp.me/scratch/5po1h
ColData* ColDataWrapper::GetColData(uint index) const {
    uint numPoints = mNumPoints;
    if (index < numPoints) {
        return &mColDataPoints[index];
    }

    uint relativeIndex = index - numPoints;
    uint numSegs = mNumSegs;
    if (relativeIndex < numSegs) {
        return &mColDataSegs[relativeIndex];
    }

    uint totalBeforeCircles = numPoints + numSegs;
    uint numCircles = mNumCircles;
    relativeIndex = index - totalBeforeCircles;
    if (mNumCircles < relativeIndex) {
        return &mColDataCircles[relativeIndex];
    }

    uint totalBeforeRects = totalBeforeCircles + numCircles;
    relativeIndex = index - totalBeforeRects;
    if (relativeIndex < mNumRects) {
        return &mColDataRects[relativeIndex];
    }

    return nullptr;
}

uint ColDataWrapper::GetNumColData() const {
    return mNumPoints + mNumSegs + mNumCircles + mNumRects;
}

void ColDataWrapper::SetOwner(ColObjTrans* pColObj) {
    for (uint i = 0; i < mNumPoints; i++) {
        mColDataPoints[i].mOwner = pColObj;
    }

    for (uint i = 0; i < mNumSegs; i++) {
        mColDataSegs[i].mOwner = pColObj;
    }

    for (uint i = 0; i < mNumCircles; i++) {
        mColDataCircles[i].mOwner = pColObj;
    }

    for (uint i = 0; i < mNumRects; i++) {
        mColDataRects[i].mOwner = pColObj;
    }
}

void ColDataWrapper::Update() {
    // not decompiled
}

void ColDataWrapper::fn_800CFD14(/* args unk */) {
    // not decompiled
}

void ColDataWrapper::NormalizeColDataSegs() {
    // not decompiled
}

void ColDataWrapper::SetFlags(u64 flags) {
    for (uint i = 0; i < mNumPoints; i++) {
        mColDataPoints[i].mFlags = flags;
    }

    for (uint i = 0; i < mNumSegs; i++) {
        mColDataSegs[i].mFlags = flags;
    }

    for (uint i = 0; i < mNumCircles; i++) {
        mColDataCircles[i].mFlags = flags;
    }

    for (uint i = 0; i < mNumRects; i++) {
        mColDataRects[i].mFlags = flags;
    }
}

void ColDataWrapper::AddFlags(u64 flags) {
    for (uint i = 0; i < mNumPoints; i++) {
        mColDataPoints[i].mFlags |= flags;
    }

    for (uint i = 0; i < mNumSegs; i++) {
        mColDataSegs[i].mFlags |= flags;
    }

    for (uint i = 0; i < mNumCircles; i++) {
        mColDataCircles[i].mFlags |= flags;
    }

    for (uint i = 0; i < mNumRects; i++) {
        mColDataRects[i].mFlags |= flags;
    }
}

void ColDataWrapper::ClearFlags(u64 flags) {
    for (uint i = 0; i < mNumPoints; i++) {
        mColDataPoints[i].mFlags &= ~flags;
    }

    for (uint i = 0; i < mNumSegs; i++) {
        mColDataSegs[i].mFlags &= ~flags;
    }

    for (uint i = 0; i < mNumCircles; i++) {
        mColDataCircles[i].mFlags &= ~flags;
    }

    for (uint i = 0; i < mNumRects; i++) {
        mColDataRects[i].mFlags &= ~flags;
    }
}

// https://decomp.me/scratch/GwUwb
u64 ColDataWrapper::CalculateFlags() const {
    u64 flags = 0;

    for (uint i = 0; i < mNumPoints; i++) {
        flags |= mColDataPoints[i].mFlags;
    }

    for (uint i = 0; i < mNumSegs; i++) {
        flags |= mColDataSegs[i].mFlags;
    }

    for (uint i = 0; i < mNumCircles; i++) {
        flags |= mColDataCircles[i].mFlags;
    }

    for (uint i = 0; i < mNumRects; i++) {
        flags |= mColDataRects[i].mFlags;
    }

    return flags;
}

// https://decomp.me/scratch/W13w9
void ColDataWrapper::fn_800D080C(bool arg1) {
    bool unk = !arg1;

    for (uint i = 0; i < mNumPoints; i++) {
        ColDataPoint* points = mColDataPoints;

        if (unk) {
            points[i].mIdentity.mEnableFlag |= 1;
        } else {
            points[i].mIdentity.mEnableFlag &= ~1;
        }
    }

    for (uint i = 0; i < mNumSegs; i++) {
        ColDataSeg* segs = mColDataSegs;

        if (unk) {
            segs[i].mIdentity.mEnableFlag |= 1;
        } else {
            segs[i].mIdentity.mEnableFlag &= ~1;
        }
    }

    for (uint i = 0; i < mNumCircles; i++) {
        ColDataCircle* circles = mColDataCircles;

        if (unk) {
            circles[i].mIdentity.mEnableFlag |= 1;
        } else {
            circles[i].mIdentity.mEnableFlag &= ~1;
        }
    }

    for (uint i = 0; i < mNumRects; i++) {
        ColDataRect* rects = mColDataRects;

        if (unk) {
            rects[i].mIdentity.mEnableFlag |= 1;
        } else {
            rects[i].mIdentity.mEnableFlag &= ~1;
        }
    }
}

// https://decomp.me/scratch/w0JbG
void ColDataWrapper::fn_800D0948(bool arg1) {
    bool unk = !arg1;

    for (uint i = 0; i < mNumPoints; i++) {
        ColDataPoint* points = mColDataPoints;

        if (unk) {
            points[i].mIdentity.mEnableFlag |= 2;
        } else {
            points[i].mIdentity.mEnableFlag &= ~2;
        }
    }

    for (uint i = 0; i < mNumSegs; i++) {
        ColDataSeg* segs = mColDataSegs;

        if (unk) {
            segs[i].mIdentity.mEnableFlag |= 2;
        } else {
            segs[i].mIdentity.mEnableFlag &= ~2;
        }
    }

    for (uint i = 0; i < mNumCircles; i++) {
        ColDataCircle* circles = mColDataCircles;

        if (unk) {
            circles[i].mIdentity.mEnableFlag |= 2;
        } else {
            circles[i].mIdentity.mEnableFlag &= ~2;
        }
    }

    for (uint i = 0; i < mNumRects; i++) {
        ColDataRect* rects = mColDataRects;

        if (unk) {
            rects[i].mIdentity.mEnableFlag |= 2;
        } else {
            rects[i].mIdentity.mEnableFlag &= ~2;
        }
    }
}

#define BOUND_DEFAULT 100000.0f

// https://decomp.me/scratch/1w90C
void ColDataWrapper::AdjustBounds() {
    mBoundsMin.Set(BOUND_DEFAULT, BOUND_DEFAULT);
    mBoundsMax.Set(-BOUND_DEFAULT, -BOUND_DEFAULT);

    for (uint i = 0; i < mNumPoints; i++) {
        ColDataPoint* point = &mColDataPoints[i];

        if (point->mPosition.x < mBoundsMin.x) {
            mBoundsMin.x = point->mPosition.x;
        }

        if (point->mPosition.y < mBoundsMin.y) {
            mBoundsMin.y = point->mPosition.y;
        }

        if (point->mPosition.x > mBoundsMax.x) {
            mBoundsMax.x = point->mPosition.x;
        }

        if (point->mPosition.y > mBoundsMax.y) {
            mBoundsMax.y = point->mPosition.y;
        }
    }

    for (uint i = 0; i < mNumSegs; i++) {
        ColDataSeg* seg = &mColDataSegs[i];

        if (seg->mStart.x < mBoundsMin.x) {
            mBoundsMin.x = seg->mStart.x;
        }

        if (seg->mStart.y < mBoundsMin.y) {
            mBoundsMin.y = seg->mStart.y;
        }

        if (seg->mStart.x > mBoundsMax.x) {
            mBoundsMax.x = seg->mStart.x;
        }

        if (seg->mStart.y > mBoundsMax.y) {
            mBoundsMax.y = seg->mStart.y;
        }

        if (seg->mEnd.x < mBoundsMin.x) {
            mBoundsMin.x = seg->mEnd.x;
        }

        if (seg->mEnd.y < mBoundsMin.y) {
            mBoundsMin.y = seg->mEnd.y;
        }

        if (seg->mEnd.x > mBoundsMax.x) {
            mBoundsMax.x = seg->mEnd.x;
        }

        if (seg->mEnd.y > mBoundsMax.y) {
            mBoundsMax.y = seg->mEnd.y;
        }
    }

    for (uint i = 0; i < mNumCircles; i++) {
        ColDataCircle* circle = &mColDataCircles[i];

        gfl::Vec3 info;
        info = circle->mInfo;

        float x = info.x;
        float y = info.y;
        float radius = info.z;

        float left = x - radius;
        float right = x + radius;

        float top = y + radius;
        float bottom = y - radius;

        if (left < mBoundsMin.x) {
            mBoundsMin.x = left;
        }

        if (bottom < mBoundsMin.y) {
            mBoundsMin.y = bottom;
        }

        if (right > mBoundsMax.x) {
            mBoundsMax.x = right;
        }

        if (top > mBoundsMax.y) {
            mBoundsMax.y = top;
        }
    }

    for (uint i = 0; i < mNumRects; i++) {
        ColDataRect* rect = &mColDataRects[i];

        if (rect->mBoundsMin.x < mBoundsMin.x) {
            mBoundsMin.x = rect->mBoundsMin.x;
        }

        if (rect->mBoundsMin.y < mBoundsMin.y) {
            mBoundsMin.y = rect->mBoundsMin.y;
        }

        if (rect->mBoundsMin.x > mBoundsMax.x) {
            mBoundsMax.x = rect->mBoundsMin.x;
        }

        if (rect->mBoundsMin.y > mBoundsMax.y) {
            mBoundsMax.y = rect->mBoundsMin.y;
        }

        if (rect->mBoundsMax.x < mBoundsMin.x) {
            mBoundsMin.x = rect->mBoundsMax.x;
        }

        if (rect->mBoundsMax.y < mBoundsMin.y) {
            mBoundsMin.y = rect->mBoundsMax.y;
        }

        if (rect->mBoundsMax.x > mBoundsMax.x) {
            mBoundsMax.x = rect->mBoundsMax.x;
        }

        if (rect->mBoundsMax.y > mBoundsMax.y) {
            mBoundsMax.y = rect->mBoundsMax.y;
        }
    }
}

void ColDataWrapper::Add(ColObj* pColObj) {
    for (uint i = 0; i < mNumPoints; i++) {
        pColObj->mTreeNode->Propagate(&mColDataPoints[i]);
    }
    for (uint i = 0; i < mNumSegs; i++) {
        pColObj->mTreeNode->Propagate(&mColDataSegs[i]);
    }
    for (uint i = 0; i < mNumCircles; i++) {
        pColObj->mTreeNode->Propagate(&mColDataCircles[i]);
    }
    for (uint i = 0; i < mNumRects; i++) {
        pColObj->mTreeNode->Propagate(&mColDataRects[i]);
    }
}

void ColDataWrapper::RemoveAll() {
    for (uint i = 0; i < mNumPoints; i++) {
        KdTreeNode::RemoveColData(&mColDataPoints[i]);
    }
    for (uint i = 0; i < mNumSegs; i++) {
        KdTreeNode::RemoveColData(&mColDataSegs[i]);
    }
    for (uint i = 0; i < mNumCircles; i++) {
        KdTreeNode::RemoveColData(&mColDataCircles[i]);
    }
    for (uint i = 0; i < mNumRects; i++) {
        KdTreeNode::RemoveColData(&mColDataRects[i]);
    }
}

void ColDataWrapper::AddAll() {
    for (uint i = 0; i < mNumPoints; i++) {
        KdTreeNode::AddColData(&mColDataPoints[i]);
    }
    for (uint i = 0; i < mNumSegs; i++) {
        KdTreeNode::AddColData(&mColDataSegs[i]);
    }
    for (uint i = 0; i < mNumCircles; i++) {
        KdTreeNode::AddColData(&mColDataCircles[i]);
    }
    for (uint i = 0; i < mNumRects; i++) {
        KdTreeNode::AddColData(&mColDataRects[i]);
    }
}
