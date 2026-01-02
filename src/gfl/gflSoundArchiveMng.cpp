#include "gflSoundArchiveMng.h"
#include "gfl/gflMemoryUtil.h"
#include "gfl/gflVec3.h"
#include "gfl_types.h"

using namespace gfl;

#define STRM_BUFFER_SIZE 0x60000

const float ZERO = 0.0f;
const float ONE = 1.0f;
const float N_ONE = -1.0f;

void SoundArchiveMng::OpenArchive(const char* brsarPath) {
    mSoundArchive.Open(brsarPath);
    u32 memSize = mSoundArchive.GetHeaderSize();
    mFileInfo = gfl::Alloc(HeapID::Sound, memSize, 0x20);
    mSoundArchive.LoadHeader(mFileInfo, memSize);
    
    memSize = mSoundArchive.GetLabelStringDataSize();
    mSymbolData = gfl::Alloc(HeapID::Sound, memSize, 0x20);
    mSoundArchive.LoadLabelStringData(mSymbolData, memSize);

    memSize = mSoundArchivePlayer.GetRequiredMemSize(&mSoundArchive);
    mSoundArchivePlayer.GetRequiredStrmBufferSize(&mSoundArchive);
    mSoundArchivePlayerMem = gfl::Alloc(HeapID::Sound, memSize, 0x20);
    mStrmBuffer = gfl::Alloc(HeapID::Sound, STRM_BUFFER_SIZE, 0x20);

    mSoundArchivePlayer.Setup(&mSoundArchive, mSoundArchivePlayerMem, memSize, mStrmBuffer, STRM_BUFFER_SIZE);
    
    memSize = mSound3DManager->GetRequiredMemSize(&mSoundArchive);
    void* buf = gfl::Alloc(HeapID::Sound, memSize, 0x20);
    mSound3DManager->Setup(&mSoundArchive, buf, memSize);

    m_298 = 0x20;

    // todo - update Sound3DListener header with the ss one
    mSound3DListeners.Insert(mSound3DListeners.GetBeginIter(), &mSound3DListener);
    
    gfl::Vec3 vec3(0.0f);
    vec3.z = 1.0f;

    gfl::Vec3 vec2(0.0f);
    vec2.y = 1.0f;

    gfl::Vec3 vec1(0.0f);
    vec1.y = 1.0f;

    nw4r::math::MTX34 mtx;
    C_MTXLookAt(mtx, (const Vec*)&vec1, (const Vec*)&vec2, (const Vec*)&vec3);
    mSound3DListener.SetMatrix(mtx);
    mSound3DListener.SetMaxVolumeDistance(ONE);
    mSound3DListener.SetUnitDistance(ONE);
    mSound3DListener.SetInteriorSize(ONE);
}

void SoundArchiveMng::ConfigureSound3DListener(const SoundListenerSettings& src) {
    mSound3DListener.SetMaxVolumeDistance(src.mMaxVolumeDistance);
    mSound3DListener.SetUnitDistance(src.mUnitDistance);
    mSound3DListener.SetInteriorSize(src.mInteriorSize);
}

void SoundArchiveMng::GetSound3DListenerConfiguration(float dst[3]) {
    dst[0] = m_2F4;
    dst[1] = m_2F8;
    dst[2] = m_2F0;
}

nw4r::snd::SoundPlayer& SoundArchiveMng::GetSoundPlayer(int arg1) {
    return mSoundArchivePlayer.GetSoundPlayer(arg1);
}
