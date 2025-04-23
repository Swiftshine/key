#ifndef FLUFF_NURBSCOUNTER_H
#define FLUFF_NURBSCOUNTER_H

#include "types.h"
#include "gfl/gflArray.h"

class NURBSCounter {
public:
    NURBSCounter(const char* name);
    ~NURBSCounter();

    inline void SetCount(size_t count) {
        mCount = count;
    }

    inline size_t GetCount() {
        return mCount;
    }

    inline void SetArray(u16* ptr) {
        mArray = ptr;
    }

    inline void CreateArray(size_t len) {
        mArray.Create(len);
    }
    
    inline void DestroyArray() {
        mArray.Destroy();
    }

    inline u16& operator[](size_t index) {
        return mArray[index];
    }
private:
    size_t mCount;
    gfl::Array<u16> mArray;
};

#endif