#include "object/FlfGameObj.h"
#include "manager/CamMng.h"
#include <revolution/MTX.h>
#include <nw4r/math.h>

namespace nw4r {
    namespace math {
        inline float SinF(float value) {
            return SinFIdx(NW4R_MATH_RAD_TO_FIDX(value));
        }
        inline float CosF(float value) {
            return CosFIdx(NW4R_MATH_RAD_TO_FIDX(value));
        }
    }
}

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
    float scaleZ;
    float scaleY;
    float scaleX;
    float sx;
    float cx;
    float sy;
    float cy;
    float cz;
    float sz;
    f32 posZ;
    f32 posY;
    f32 posX;
    float cx_cz;
    float sx_sz;
    float sx_cz;
    float cx_sz;
    
    scaleX = mScale.x;
    scaleY = mScale.y;
    scaleZ = mScale.z;
    
    sx = nw4r::math::SinF(mRotation.x);
    cx = nw4r::math::CosF(mRotation.x);
    sy = nw4r::math::SinF(mRotation.y);
    cy = nw4r::math::CosF(mRotation.y);
    sz = nw4r::math::SinF(mRotation.z);
    cz = nw4r::math::CosF(mRotation.z);

    posX = mPosition.x;
    posY = mPosition.y;
    posZ = mPosition.z;
    
    cx_sz = cx * sz;
    sx_sz = sx * sz;
    sx_cz = sx * cz;
    cx_cz = cx * cz;

    
    mMatrix[0][0] = cz * cy * scaleX;
    mMatrix[0][1] = (sx_cz * sy - cx_sz) * scaleY;
    mMatrix[0][2] = (cx_cz * sy + sx_sz) * scaleZ;
    mMatrix[0][3] = posX;
    
    mMatrix[1][0] = (sz * cy) * scaleX;
    mMatrix[1][1] = ((sx_sz * sy) + cx_cz) * scaleY;
    mMatrix[1][2] = ((cx_sz * sy) - sx_cz) * scaleZ;
    mMatrix[1][3] = posY;
    
    mMatrix[2][0] = scaleX * -sy;
    mMatrix[2][1] = cy * sx * scaleY;
    mMatrix[2][2] = cy * cx * scaleZ;
    mMatrix[2][3] = posZ;
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
