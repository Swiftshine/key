#include "gflTimer.h"

using namespace gfl;

Timer::Timer()
    : mOSTime(0)
    , m_10(0)
    , m_18(0)
{ }

Timer::~Timer() { }

void Timer::SetOSTime() {
    mOSTime = OSGetTime();
}

void Timer::fn_80646EDC() {
    // not decompiled

    
    // if (mOSTime != 0) {
    //     u64 time = OSGetTime();
    //     m_10 = time;

    //     u64 temp;

    //     if (time >= mOSTime) {
    //         temp = 0;
    //     } else {
    //         temp = time - mOSTime;
    //     }

    //     m_18 = temp;
    //     mOSTime = 0;
    //     m_10 = 0;
    // }
}


void Timer::ResetTime() {
    mOSTime = 0;
    m_10 = 0;
    m_18 = 0;
}

u64 Timer::fn_80646FA4(u64* first, u64* second) {
    // not decompiled
    return 0;
}
