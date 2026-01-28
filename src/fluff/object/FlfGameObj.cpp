#include "object/FlfGameObj.h"
#include "manager/CamMng.h"
#include <revolution/MTX.h>
#include <nw4r/math.h>

FlfGameObj::FlfGameObj(uint category)
    : mPosition(0.0f)
    , mRotation(0.0f)
    , mScale(1.0f)
    , mMatrix()
    , mFlags(0)
    , m_64(0)
    , mCategory(category)
    , m_6C(false)
    , mIsCulled(false)
    , mShouldUpdateWater(true)
    , m_6F(false)
    , mCullThreshold(18.666666f)
    , mDirection(Direction::Forward)
    , m_78(2)
    , m_7C(false)
    , m_7D(false)
{
    PSMTXIdentity(mMatrix);
}

FlfGameObj::~FlfGameObj() { }

void FlfGameObj::UpdateMatrix() {
    MTX34_INIT(mMatrix, mPosition, mRotation, mScale);
}

void FlfGameObj::vf10(bool val) {
    m_6C = val;
}

bool FlfGameObj::vf14() {
    return m_6C;
}

void FlfGameObj::SetCulled(bool arg1) {
    if (mShouldUpdateWater) {
        if (mIsCulled != arg1) {
            UpdateWater(arg1);
            mIsCulled = arg1;
        }
    } else if (mIsCulled) {
        UpdateWater(false);
        mIsCulled = false;
    }
}

bool FlfGameObj::ShouldCull(CamMng* pCamMgr) {
    ScreenPosition screenPos = GetScreenPosition();
    return pCamMgr->ShouldCull(screenPos);
}
