#include "gflRenderObj.h"
#include "gflMemoryUtil.h"
#include "gflMemory.h"

#include "gflScene.h"

using namespace gfl;

RenderObj::RenderObj() {
    mScene = nullptr;
    m_C = true;
    m_D = true;
    mShouldUpdate = true;
    mIsActive = false;
    m_10 = 0.0f;
    m_14 = 0;

    gfl::Memory::InitIfNotInited();
    mAllocator = &gfl::Memory::Instance()->GetHeapByAddress(this)->GetAllocator1();
}

RenderObj::~RenderObj() {
    if (nullptr != mScene) {
        mScene->RemoveRenderObj(this);
        mScene = nullptr;
    }
}

void RenderObj::SetUpdate(bool arg1) {
    vf18(arg1);
    Update(arg1);
}

void RenderObj::vf18(bool arg1) {
    m_C = arg1;

    if (nullptr == mScene) {
        return;
    }

    mScene->HandleRenderObj(this);
}

void RenderObj::vf20(bool arg1) {
    m_D = arg1;

    if (mIsActive) {
        Update(arg1);
    }

    if (nullptr != mScene) {
        mScene->HandleRenderObj(this);
    }
}

// https://decomp.me/scratch/EKLdu
bool RenderObj::vf34(float& arg0, float& arg1, float& arg2, float& arg3) {
    // bool b;
    // float f1;
    // float f2;
    // float f3;

    // if (!vf1C()) {
    //     b = true;
    // } else {
    //     f3 = vf2C();

    //     if (0.0f > f3) {
    //         vf28(f1);
    //         if ((arg0 - f1) * (arg0 - f1) <= (arg2 + f3) * (arg2 + f3)) {
    //             b = (arg3 + f3) * (arg3 + f3) < (arg1 - f2) * (arg1 - f2);
    //         } else {
    //             b = true;
    //         }
    //     } else {
    //         b = false;
    //     }
    // }

    return 0;
}

void RenderObj::Update(bool arg1)  {
    mShouldUpdate = arg1;

    if (nullptr == mScene) {
        return;
    }

    mScene->HandleRenderObj(this);
}

void RenderObj::SetActive(bool state) {
    mIsActive = state;
}

nw4r::g3d::G3dObj* RenderObj::GetObject() {
    return nullptr;
}

// not decompiled
bool RenderObj::XluSortCheck(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj) {
    return 0;
}

// not decompiled
bool RenderObj::OpaSortCheck(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj) {
    return 0;
}
