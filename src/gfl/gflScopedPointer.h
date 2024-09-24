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

    inline void Destroy() {
        delete mPointer;
        mPointer = nullptr;
    }

    inline void operator=(T* other) {
        mPointer = other;
    }

    inline T* Get() const {
        return mPointer;
    }

    inline T& operator*() {
        return *mPointer;
    }
    inline T* operator->() const {
        return mPointer;
    }

    inline T** operator&() {
        return &mPointer;
    }

    inline bool operator==(T* other) const {
        return mPointer == other;
    }

    inline friend bool operator==(T* other, const ScopedPointer<T>& obj) {
        return other == obj.Get();
    }

    inline bool operator!=(T* other) const {
        return mPointer != other;
    }

    inline bool IsValid() const {
        return nullptr != mPointer;
    }

private:
    T* mPointer;
};

}

#endif
