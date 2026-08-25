#ifndef GFL_SOUNDARCHIVEMNG_H
#define GFL_SOUNDARCHIVEMNG_H

#include <nw4r/snd.h>

namespace gfl {
    class SoundArchiveMng {
    public:
        struct SoundListenerSettings {
            f32 mMaxVolumeDistance;
            f32 mUnitDistance;
            f32 mInteriorSize;
        };

    public:
        inline SoundArchiveMng() { }
        ~SoundArchiveMng();

        virtual void ConfigureSound3DListener(const SoundListenerSettings&);
        virtual void GetSound3DListenerConfiguration(f32 dst[3]);
        
        void OpenArchive(const char* path);
        nw4r::snd::SoundPlayer& GetSoundPlayer(s32);
    private:
        nw4r::snd::DvdSoundArchive mSoundArchive;
        nw4r::snd::SoundArchivePlayer mSoundArchivePlayer;
        s32 m_270;
        s32 m_274;
        s32 m_278;
        nw4r::snd::Sound3DManager* mSound3DManager;
        s32 m_280;
        nw4r::ut::LinkList<nw4r::snd::Sound3DListener, 0> mSound3DListeners;
        s32 m_290;
        s32 m_294;
        s32 m_298;
        s32 m_29C;
        s32 m_2A0;
        s32 m_2A4;
        nw4r::snd::Sound3DListener mSound3DListener;
        s32 m_2E4;
        s32 m_2E8;
        s32 m_2EC;
        f32 m_2F0;
        f32 m_2F4;
        f32 m_2F8;
        s32 m_2FC;
        s32 m_300;
        nw4r::ut::LinkList<nw4r::math::VEC3, 0> mList2;
        u32 m_310;
        void* mFileInfo;
        void* mSymbolData;
        void* mSoundArchivePlayerMem;
        void* mStrmBuffer;
    };
    
    ASSERT_SIZE(SoundArchiveMng, 0x324);
}

#endif
