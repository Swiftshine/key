#ifndef GFL_SOUNDARCHIVEMNG_H
#define GFL_SOUNDARCHIVEMNG_H

#include <nw4r/snd.h>

namespace gfl {
    class SoundArchiveMng {
    public:
        struct SoundListenerSettings {
            float mMaxVolumeDistance;
            float mUnitDistance;
            float mInteriorSize;
        };

    public:
        inline SoundArchiveMng() { }
        ~SoundArchiveMng();

        virtual void ConfigureSound3DListener(const SoundListenerSettings&);
        virtual void GetSound3DListenerConfiguration(float dst[3]);
        
        void OpenArchive(const char* path);
        nw4r::snd::SoundPlayer& GetSoundPlayer(int);
    private:
        nw4r::snd::DvdSoundArchive mSoundArchive;
        nw4r::snd::SoundArchivePlayer mSoundArchivePlayer;
        int m_270;
        int m_274;
        int m_278;
        nw4r::snd::Sound3DManager* mSound3DManager;
        int m_280;
        nw4r::ut::LinkList<nw4r::snd::Sound3DListener, 0> mSound3DListeners;
        int m_290;
        int m_294;
        int m_298;
        int m_29C;
        int m_2A0;
        int m_2A4;
        nw4r::snd::Sound3DListener mSound3DListener;
        int m_2E4;
        int m_2E8;
        int m_2EC;
        float m_2F0;
        float m_2F4;
        float m_2F8;
        int m_2FC;
        int m_300;
        nw4r::ut::LinkList<nw4r::math::VEC3, 0> mList2;
        uint m_310;
        void* mFileInfo;
        void* mSymbolData;
        void* mSoundArchivePlayerMem;
        void* mStrmBuffer;
    };
    
    ASSERT_SIZE(SoundArchiveMng, 0x324);
}

#endif
