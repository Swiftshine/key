#include "gflSD3DActor.h"

using namespace gfl;

SD3DActorWrapper::SD3DActorWrapper()
    : mActor()
{
    mSub[0].m_0 = -1;
    mSub[1].m_0 = -1;
    mSub[2].m_0 = -1;
    mSub[3].m_0 = -1;
}

inline SD3DActor::~SD3DActor() {
    Sound::Instance()->DestroySD3DActorInner(mActorInner);
}

SD3DActor::SubStruct::SubStruct()
    : m_4(0)
    , m_8(0)
{ }

SD3DActor::SubStruct::~SubStruct() { }

SD3DActorWrapper::~SD3DActorWrapper() { }

void SD3DActorWrapper::SetPosition(const nw4r::math::VEC2& rSrc) {
    nw4r::math::VEC3 vec(rSrc.x, rSrc.y, 0.0f);
    mActor.SetPosition(vec);
}

void SD3DActor::SetPosition(const nw4r::math::VEC3& rSrc) {
    mActorInner->SetPosition(rSrc);
}

nw4r::math::VEC3 SD3DActorWrapper::GetPosition() {
    return mActor.GetPosition();
}

nw4r::math::VEC3 SD3DActor::GetPosition() {
    return mActorInner->GetPosition();
}

void SD3DActorWrapper::fn_802CFDAC(nw4r::math::VEC2& rDst, float arg2, int arg3) {

}

void SD3DActor::vf14(nw4r::math::VEC3& rDst, float arg2, int arg3) {
    
}