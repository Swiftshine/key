#ifndef GFL_TIMER_H
#define GFL_TIMER_H

#include "types.h"
#include <revolution/OS.h>

namespace gfl {

    class Timer {
    public:
        Timer();
        virtual ~Timer();
        void SetOSTime();
        void fn_80646EDC();
        void ResetTime();
        u64 fn_80646FA4(u64* arg1, u64* arg2);
    private:
        uint m_4; // padding?
        u64 mOSTime; // @ 0x8
        u64 m_10;
        u64 m_18;
    };

    ASSERT_SIZE(Timer, 0x20);
}
#endif
