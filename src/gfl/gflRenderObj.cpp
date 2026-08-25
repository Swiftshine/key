#pragma readonly_strings on

#include "gflRenderObj.h"
#include "gflMemoryUtil.h"
#include "gflMemory.h"
#include "gflScene.h"

using namespace gfl;

RenderObj::RenderObj()
    : mScene(nullptr)
    , mIsVisible(true)
    , m_D(true)
    , mShouldUpdate(true)
    , mIsActive(false)
    , mUpdateRate(0.0f)
    , m_14(0)
{
    mAllocator = &gfl::Memory::TryGetInstance()->GetHeapByAddress(this)->GetAllocator1();
}

RenderObj::~RenderObj() {
    if (nullptr != mScene) {
        mScene->RemoveRenderObj(this);
        mScene = nullptr;
    }
}

void RenderObj::SetUpdate(bool arg1) {
    SetVisibility(arg1);
    Update(arg1);
}

void RenderObj::SetVisibility(bool arg1) {
    mIsVisible = arg1;

    if (mScene == nullptr) {
        return;
    }

    mScene->HandleRenderObj(this);
}

void RenderObj::vf20(bool arg1) {
    m_D = arg1;

    if (mIsActive) {
        Update(arg1);
    }

    if (mScene != nullptr) {
        mScene->HandleRenderObj(this);
    }
}

bool RenderObj::vf34(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (!vf1C()) {
        return true;
    }

    f32 updateRate = GetUpdateRate();

    if (updateRate <= 0.0f) {
        return false;
    }

    gfl::Vec3 vec = vf28();

    f32 temp = (arg0 - vec.x);
    f32 temp2 = (arg2 + updateRate);

    if (temp * temp > temp2 * temp2) {
        return true;
    }

    f32 temp3 = (arg1 - vec.y);
    f32 temp4 = (arg3 + updateRate);

    return temp3 * temp3 > temp4 * temp4;
}

void RenderObj::Update(bool arg1)  {
    mShouldUpdate = arg1;

    if (mScene == nullptr) {
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
