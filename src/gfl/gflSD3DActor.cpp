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
    mSoundHandle.SetPosition(nullptr);
    mSoundHandle.SetInnerSoundHandle(nullptr);
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
    SoundHandle handle = GetSoundHandle(soundID, 0, arg6);

    if (handle.HandlePositionValid()) {
        Sound::Instance()->fn_8064D288(arg1, handle.GetInnerSoundHandle(), 0);
    }

    if (handle.HandlePositionValid()) {
        Sound::Instance()->fn_8064D2B4(arg2, handle.GetInnerSoundHandle());
    }

    return handle;
}


void SD3DActorWrapper::fn_802CFF80(int soundID, int arg2, bool add) {
    if (soundID == -1) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (!mInfo[i].CheckSoundID(soundID)) {
            continue;
        }

        if (InfoHandlePositionValid(i)) {
            if (mInfo[i].mSoundHandle.HandlePositionValid()) {
                Sound::Instance()->ManageSoundHandleInner(mInfo[i].mSoundHandle.GetInnerSoundHandle(), arg2, add);
            }
        }

        InvalidateInfoSoundID(&mInfo[i]);
    }
}

void SD3DActorWrapper::fn_802D0074(int arg2, bool add) {
    for (int i = 0; i < 4; i++) {
        if (mInfo[i].CheckSoundID(-1)) {
            continue;
        }

        if (mInfo[i].mSoundHandle.HandlePositionValid()) {
            Sound::Instance()->ManageSoundHandleInner(mInfo[i].mSoundHandle.GetInnerSoundHandle(), arg2, add);
        }

        InvalidateInfoSoundID(&mInfo[i]);
    }
}

bool SD3DActorWrapper::HasSoundID(int soundID) {
    bool ret = false;
    
    if (soundID == -1) {
        return false;
    }

    SD3DActorInfo* info = &mInfo[0];

    for (int i = 0; i < 4; i++, info++) {
        if (info->CheckSoundID(soundID)) {        
            if (info->HandlePositionValid()) {
                ret = true;
                break;
            }
        }
    }

    return ret;
}

SD3DActorInfo* SD3DActorWrapper::GetSD3DActorInfo() {
    int index = GetMatchingIndex(-1);

    if (index < 0) {
        fn_802D02B0();
        index = GetMatchingIndex(-1);
    }

    if (index >= 0) {
        return &mInfo[index];
    }

    return nullptr;
}

void SD3DActorWrapper::InvalidateInfoSoundID(SD3DActorInfo* pInfo) {
    if (pInfo != nullptr) {
        pInfo->mSoundID = -1;
    }
}

int SD3DActorWrapper::GetMatchingIndex(int soundID) {
    int result = -1;

    if (mInfo[0].mSoundID == soundID) {
        result = 0;
    } else if (mInfo[1].mSoundID == soundID) {
        result = 1;
    } else if (mInfo[2].mSoundID == soundID) {
        result = 2;
    } else if (mInfo[3].mSoundID == soundID) {
        result = 3;
    }

    return result;
}

void SD3DActorWrapper::fn_802D02B0() {
    for (int i = 0; i < 4; i++) {
        if (mInfo[i].CheckSoundID(-1)) {
            continue;
        }

        if (!InfoHandlePositionValid(i)) {
            InvalidateInfoSoundID(&mInfo[i]);
        }
    }
}
