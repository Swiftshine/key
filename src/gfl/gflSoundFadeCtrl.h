#ifndef GFL_SOUNDFADECTRL_H
#define GFL_SOUNDFADECTRL_H

namespace gfl {

    class SoundFadeCtrl {
    private:
        static SoundFadeCtrl* sInstance;
    public:
        virtual ~SoundFadeCtrl();
        virtual void vfC(float, s32, s32);
        
        static inline SoundFadeCtrl* Instance() {
            return sInstance;
        }

        static inline void SetInstance(SoundFadeCtrl* inst) {
            sInstance = inst;
        }
    };
}

#endif
