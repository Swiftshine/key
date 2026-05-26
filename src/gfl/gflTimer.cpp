#pragma readonly_strings on

#include "gflTimer.h"
#include "OS/OSTime.h"

using namespace gfl;

Timer::Timer()
    : mStartTime(0)
    , mEndTime(0)
    , mDelta(0)
{ }

Timer::~Timer() { }

void Timer::Start() {
    mStartTime = OSGetTime();
}

void Timer::End() {
    if (mStartTime == 0) {
        return;
    }

    s64 delta = 0;
    s64 time = OSGetTime();
    mEndTime = time;
    
    if (mEndTime <= mStartTime) {
        delta = 0;
    } else {
        delta = mEndTime - mStartTime;
    }

    mDelta += delta;
    mStartTime = 0;
    mEndTime = 0;
}


void Timer::Reset() {
    mStartTime = 0;
    mEndTime = 0;
    mDelta = 0;
}

s64 Timer::GetDelta(s64* pFirst, s64* pSecond) {
    s64 second = *pSecond;
    s64 first = *pFirst;

    if (first <= second) {
        return 0;
    }


    return first - second;
}
