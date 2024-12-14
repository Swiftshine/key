#include "gflSoundArchiveMng.h"
#include "gfl/gflMemoryUtil.h"
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
    NW4R_LINKLIST_ASSERT(this);

    // nw4r::ut::detail::LinkListImpl::Insert(&this->mListNode,&local_88,&(this->mList).mNode.mPrev)
    
    Vec vec3;
    vec3.x = ZERO + ZERO;
    vec3.y = ZERO + ZERO;
    vec3.z = ZERO + N_ONE;

    Vec vec2;
    vec2.x = ZERO;
    vec2.y = ONE;
    vec2.z = ZERO;

    Vec vec1;
    vec1.x = ZERO;
    vec1.y = ONE;
    vec1.z = ZERO;
    nw4r::math::MTX34 mtx;
    C_MTXLookAt(mtx, &vec1, &vec2, &vec3);
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
