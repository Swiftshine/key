#include "gflSD3DActor.h"
#include "gflSoundHandle.h"

using namespace gfl;

#define IF_HANDLE_POS_EQUAL(handle, code) { \
    bool eq; \
    SoundHandleInner* inner = handle.mSoundHandleInner; \
    if (inner != nullptr) { \
        eq = handle.mPosition == inner->mPosition; \
    } else { \
        eq = false; \
    } \
    if (eq) code \
}

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
    SoundHandle handle = GetSoundHandle(soundID, 0, arg6);

    IF_HANDLE_POS_EQUAL(handle, {
        Sound::Instance()->fn_8064D288(arg1, inner, 0);
    })

    IF_HANDLE_POS_EQUAL(handle, {
        Sound::Instance()->fn_8064D2B4(arg2, inner);
    })

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

        bool valid;

        IF_HANDLE_POS_EQUAL(mInfo[i].mSoundHandle, {
            valid = Sound::Instance()->ValidateSoundHandleSound(inner);
        } else {
            valid = false;
        })

        if (valid) {
            IF_HANDLE_POS_EQUAL(mInfo[i].mSoundHandle, {
                Sound::Instance()->ManageSoundHandleInner(inner, arg2, add);
            })
        }

        InvalidateInfoSoundID(&mInfo[i]);
    }
}

void SD3DActorWrapper::fn_802D0074(int arg2, bool add) {
    for (int i = 0; i < 4; i++) {
        if (mInfo[i].CheckSoundID(-1)) {
            continue;
        }

        IF_HANDLE_POS_EQUAL(mInfo[i].mSoundHandle, {
            Sound::Instance()->ManageSoundHandleInner(inner, arg2, add);
        })

        InvalidateInfoSoundID(&mInfo[i]);
    }
}

// https://decomp.me/scratch/o6SVQ
bool SD3DActorWrapper::HasSoundID(int soundID) {
    bool ret = false;
    
    if (soundID == -1) {
        return false;
    }


    for (int i = 0; i < 4; i++) {
        if (!mInfo[i].CheckSoundID(soundID)) {
            continue;
        }

        bool valid;

        IF_HANDLE_POS_EQUAL(mInfo[i].mSoundHandle, {
            valid = Sound::Instance()->ValidateSoundHandleSound(inner);
        } else {
            valid = false;
        })

        if (valid) {
            ret = true;
            break;
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

        bool valid;

        IF_HANDLE_POS_EQUAL(mInfo[i].mSoundHandle, {
            valid = Sound::Instance()->ValidateSoundHandleSound(inner);
        } else {
            valid = false;
        })

        if (!valid) {
            InvalidateInfoSoundID(&mInfo[i]);
        }
    }
}
