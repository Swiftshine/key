#ifndef GFL_SCOPEDPOINTER_H
#define GFL_SCOPEDPOINTER_H

#include "types.h"

namespace gfl {
template <typename T>
class ScopedPointer {
public:
    inline ScopedPointer() { }

    inline ~ScopedPointer() {
        delete mPointer;
        mPointer = nullptr;
    }

    inline void Reset() {
        mPointer = nullptr;
    }

    inline void operator=(T* other) {
        mPointer = other;
    }

    inline T* get() { return mPointer; }
    inline T& operator*() { return *mPointer; }
    inline T* operator->() const { return mPointer; }

private:
    T* mPointer;
};

}

#endif