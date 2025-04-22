#ifndef GFLARRAY_H
#define GFLARRAY_H

#include "gflMemoryUtil.h"

namespace gfl {

    template <typename T>
    class Array {
    public:
        inline Array() { }
        
        inline ~Array() {
            delete[] mArray;
            mArray = nullptr;
        }

        inline void Create(size_t len) {
            T* temp = new (gfl::HeapID::Work) T[len];

            if (!temp) {
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

        inline void operator=(T* other) {
            mArray = other;
        }

        inline T* get() {
            return mArray;
        }

        inline T* ptr() {
            return mArray;
        }

        operator T*() const {
            return mArray;
        }
        
    private:
        T* mArray;
    };

    template <typename T, uint N>
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

    template <typename T>
    class CountedArray {
    public:
        inline CountedArray() { }
        inline ~CountedArray() { }

        inline T& operator[](size_t index) {
            return mArray[index];
        }

        inline void Create(T* ptr) {
            if (ptr == nullptr) {
                Destroy();
            } else {
                mArray = ptr;
            }
        }

        inline void Destroy() {
            delete mArray;
            mArray = nullptr;
        }

        inline void SetCount(size_t count) {
            mCount = count;
        }

        inline void Set(T* ptr) {
            mArray = ptr;
        }

        inline T* Get() {
            return mArray;
        }
    private:
        size_t mCount;
        T* mArray;
    };
}

#endif
