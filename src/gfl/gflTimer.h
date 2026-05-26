#ifndef GFL_TIMER_H
#define GFL_TIMER_H

#include "types.h"
#include <revolution/OS.h>

namespace gfl {

    class Timer {
    public:
        Timer();
        virtual ~Timer();
        
        void Start();
        void End();
        void Reset();
        s64 GetDelta(s64* pFirst, s64* pSecond);
    private:
        /* 0x08 */ s64 mStartTime;
        /* 0x10 */ s64 mEndTime;
        /* 0x18 */ s64 mDelta;
    };

    ASSERT_SIZE(Timer, 0x20);
}
#endif
