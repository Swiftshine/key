#ifndef FLUFF_NURBSOption_H
#define FLUFF_NURBSOption_H

#include "types.h"
#include "gfl/gflArray.h"

class NURBSOption {
public:
    NURBSOption(const char* name);
    ~NURBSOption();

    s16 GetOption(float arg0);
    
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