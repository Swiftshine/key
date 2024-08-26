#ifndef GFL_SCOPEDPOINTER_H
#define GFL_SCOPEDPOINTER_H

#include "types.h"
#include "gflMemoryUtil.h"

namespace gfl {
template <typename T>
class ScopedPointer {
public:
    inline ScopedPointer() { }
    inline ScopedPointer(T* other) { mPointer = other; }
    inline ~ScopedPointer() {
        delete mPointer;
        mPointer = nullptr;
    }
    void Create() {
        mPointer = new T;
    }

    void Create(u8 heapID) {
        T* temp = new (heapID) T;

        if (!temp) {
            delete mPointer;
            mPointer = nullptr;
        } else {
            mPointer = temp;
        }
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