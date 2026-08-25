#ifndef GFLARRAY_H
#define GFLARRAY_H

#include "gflMemoryUtil.h"

namespace gfl {

    template <typename T>
    class Array {
    public:
        inline Array() { }

        inline Array(T* ptr)
            : mArray(ptr)
        { }

        inline ~Array() {
            delete[] mArray;
            mArray = nullptr;
        }

        inline void Create(size_t len) {
            T* temp = new (gfl::eHeapID_Work) T[len];

            if (temp == nullptr) {
                Destroy();
            } else {
                mArray = temp;
            }
        }

        inline void Destroy() {
            delete[] mArray;
            mArray = nullptr;
        }

        inline T& operator[](unsigned long index) {
            return mArray[index];
        }

        inline const T& operator[](u32 index) const {
            return mArray[index];
        }

        inline void operator=(T* other) {
            mArray = other;
        }

        inline T* get() {
            return mArray;
        }

        inline T* ptr() {
            return mArray;
        }

        // operator T*() const {
        //     return mArray;
        // }

    private:
        T* mArray;
    };

    template <typename T, u32 N>
    class FixedArray {
    public:
        inline FixedArray() { }
        inline ~FixedArray() { }

        inline T& operator[](size_t index) {
            return mArray[index];
        }

        inline T* get() { return mArray; }
    private:
        T mArray[N];
    };
}

#endif
