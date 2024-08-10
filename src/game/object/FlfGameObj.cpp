#include <game/object/FlfGameObj.h>
#include <nw4r/math/math_triangular.h>

namespace nw4r {
    namespace math {
        float SinF(float);
        float CosF(float);
    }
}

FlfGameObj::FlfGameObj(u32 newActorType) {
    mPosition = 0.0f;
    mRotation = 0.0f;
    mScale    = 1.0f;

    mMatrix[0][0] = 0.0f;
    mMatrix[0][1] = 0.0f;
    mMatrix[0][2] = 0.0f;
    mMatrix[0][3] = 0.0f;
    mMatrix[1][0] = 0.0f;
    mMatrix[1][1] = 0.0f;
    mMatrix[1][2] = 0.0f;
    mMatrix[1][3] = 0.0f;
    mMatrix[2][0] = 0.0f;
    mMatrix[2][1] = 0.0f;
    mMatrix[2][2] = 0.0f;
    mMatrix[2][3] = 0.0f;

    mFlags = 0;
    m_64 = 0;
    mType = newActorType;
    m_6C = false;
    m_6D = false;
    m_6E = true;
    m_6F = false;
    mCullThreshold = CameraManager::CullingThreshold;
    m_74 = 0;
    m_78 = 2;
    m_7C = false;
    m_7D = false;

    fn_8066E8A0((void*)&this->mMatrix);
}

FlfGameObj::~FlfGameObj() { }

void FlfGameObj::UpdateMatrix() {
    f32 cosRotZ;
    f32 temp_f4;
    f32 temp_f9;
    f32 temp_f10;
    f32 temp_f11;
    f32 sinRotY;
    f32 cosRotY;
    f32 sinRotZ;
    f32 scaleX;
    f32 scaleY;
    f32 scaleZ;
    f32 sinRotX;
    f32 cosRotX;

    scaleX = this->mScale.x;
    scaleY = this->mScale.y;
    scaleZ = this->mScale.z;
    
    sinRotX = nw4r::math::SinF(this->mRotation.x);
    cosRotX = nw4r::math::CosF(this->mRotation.x);
    sinRotY = nw4r::math::SinF(this->mRotation.y);
    cosRotY = nw4r::math::CosF(this->mRotation.y);
    sinRotZ = nw4r::math::SinF(this->mRotation.z);
    cosRotZ  = nw4r::math::CosF(this->mRotation.z);

    
    temp_f11 = cosRotX * sinRotZ;
    temp_f9 = sinRotX * sinRotZ;
    temp_f10 = sinRotX * cosRotZ;
    temp_f4 = cosRotX * cosRotZ;

    mMatrix[0][3] = mPosition.x;
    mMatrix[1][3] = mPosition.y;
    mMatrix[2][3] = mPosition.z;

    
    mMatrix[0][0] = scaleX * (cosRotZ * cosRotY);
    mMatrix[0][1] = scaleY * ((temp_f10 * sinRotY) - temp_f11);
    mMatrix[0][2] = scaleZ * ((temp_f4 * sinRotY) + temp_f9);
    
    mMatrix[1][0] = scaleX * (sinRotZ * cosRotY);
    mMatrix[1][1]= scaleY * ((temp_f9 * sinRotY) + temp_f4);
    mMatrix[1][2] = scaleZ * ((temp_f11 * sinRotY) - temp_f10);
    
    mMatrix[2][0] = scaleX * -sinRotY;
    mMatrix[2][1]= scaleY * (cosRotY * sinRotX);
    mMatrix[2][2] = scaleZ * (cosRotY * cosRotX);
}

void FlfGameObj::vf10(bool val) {
    m_6C = val;
}

bool FlfGameObj::vf14() {
    return fn_8078A5A0(this);
}

void FlfGameObj::fn_8002C004(bool arg1) {
    if (m_6E) {
        if (m_6D != arg1) {
            vf64(arg1);
            m_6D = arg1;
        }
    } else if (m_6D) {
        vf64(false);
        m_6D = false;
    }
}


bool FlfGameObj::ShouldCull(CameraManager* camMgr) {
    Vec3f screenPos = GetScreenPos();
    return camMgr->CheckCull(&screenPos);
}

// the rest of the functions are not implemented in this tu
