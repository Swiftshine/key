#ifndef GFL_SOUNDQUE_H
#define GFL_SOUNDQUE_H

#include "gflLinkedList.h"
#include "gflSoundHandleInner.h"

namespace gfl {
    class SoundQue {
    public:
        inline SoundQue() {}
        virtual ~SoundQue();
        
        void fn_8064B314(); // static?
        void RemoveAll();
        void Remove(SoundHandleInner* soundHandle);
    private:
        gfl::LinkedList<SoundHandleInner> mQueue;
    };
}

#endif
