#include "gflSD3DActor.h"
#include "gflSoundHandle.h"

using namespace gfl;

SD3DActorWrapper::SD3DActorWrapper()
    : mActor()
{
    mInfo[0].mSoundID = -1;
    mInfo[1].mSoundID = -1;
    mInfo[2].mSoundID = -1;
    mInfo[3].mSoundID = -1;
}

inline SD3DActor::~SD3DActor() {
    Sound::Instance()->DestroySD3DActorInner(mActorInner);
}

SD3DActorInfo::SD3DActorInfo() {
    mSoundHandle.mPosition = nullptr;
    mSoundHandle.mSoundHandleInner = nullptr;
}

SD3DActorInfo::~SD3DActorInfo() { }

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

SoundHandle SD3DActorWrapper::GetSoundHandle(int soundID, int arg2, int arg3) {
    fn_802D02B0();
    SD3DActorInfo* info = GetSD3DActorInfo();

    if (info == nullptr) {
        return SoundHandle(nullptr, nullptr);
    }

    if (soundID != -1) {
        info->mSoundID = soundID;
        info->mSoundHandle = mActor.GetSoundHandle(soundID, arg2, arg3);
        return info->mSoundHandle;
    }

    return SoundHandle(nullptr, nullptr);
}

SoundHandle SD3DActor::GetSoundHandle(int soundID, int arg2, int arg3) {
    const SoundHandle& handle = mActorInner->GetSoundHandle(soundID, arg2, arg3);
    return handle;
}

SoundHandle SD3DActorWrapper::fn_802CFEBC(
    float arg1,
    float arg2,
    int soundID,
    int arg5,
    int arg6
) {
    SoundHandle rHandle = GetSoundHandle(soundID, 0, arg6);
    SoundHandleInner* inner = rHandle.mSoundHandleInner;

    bool unk;

    if (inner != nullptr) {
        unk = rHandle.mPosition == inner->mPosition;
    } else {
        unk = false;
    }

    if (unk) {
        Sound::Instance()->fn_8064D288(arg1, inner, 0);
    }

    inner = rHandle.mSoundHandleInner;

    if (inner != nullptr) {
        unk = rHandle.mPosition == inner->mPosition;
    } else {
        unk = false;
    }

    if (unk) {
        Sound::Instance()->fn_8064D2B4(arg2, inner);
    }

    return rHandle;
}
