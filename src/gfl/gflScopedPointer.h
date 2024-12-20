#ifndef GFL_SCOPEDPOINTER_H
#define GFL_SCOPEDPOINTER_H

#include "types.h"
#include "gflMemoryUtil.h"

namespace gfl {

    template <typename T>
    class PointerBase {
    public:
        inline PointerBase() { }
        inline PointerBase(T* ptr) { }

        inline void Create() { }
        inline void Create(T* ptr) { }
        inline void Create(u8 heapID) { }

        inline void Destroy() { }

        inline void operator=(T* ptr) {
            mPointer = ptr;
        }

        inline bool operator==(T* other) const {
            return mPointer == other;
        }

        inline bool operator==(PointerBase* other) const {
            return mPointer == other->Get();
        }

        inline bool operator!=(T* other) const {
            return mPointer != other;
        }

        inline bool operator!=(PointerBase* other) const {
            return mPointer != other->Get();
        }

        inline T& operator*() const {
            return *mPointer;
        }

        inline T* operator->() const {
            return mPointer;
        }

        inline T* Get() const {
            return mPointer;
        }

        inline T* ptr() const {
            return mPointer;
        }

        inline bool IsValid() const {
            return nullptr != mPointer;
        }
    protected:
        T* mPointer;
    };

    template <typename T>
    static inline bool operator==(T* lhs, PointerBase<T>& rhs) {
        return rhs == lhs;
    }

    template <typename T>
    static inline bool operator!=(T* lhs, PointerBase<T>& rhs) {
        return rhs != lhs;
    }

    template <typename T>
    static inline bool operator==(int lhs, PointerBase<T>& rhs) {
        return rhs == (T*)lhs;
    }

    template <typename T>
    static inline bool operator!=(int lhs, PointerBase<T>& rhs) {
        return (T*)lhs != rhs;
    }


    template <typename T>
    class ScopedPointer : public PointerBase<T> {
    public:
        inline ScopedPointer() { }
        inline ScopedPointer(T* ptr) {
            mPointer = ptr;
        }

        inline ~ScopedPointer() {
            delete mPointer;
            mPointer = nullptr;
        }

        inline void Create() {
            mPointer = new T;
        }

        inline void Create(T* ptr) {
            if (nullptr == ptr) {
                Destroy();
            } else {
                mPointer = ptr;
            }
        }

        inline void Create(u8 heapID) {
            T* ptr = new (heapID) T;

            if (!ptr) {
                Destroy();
            } else {
                mPointer = ptr;
            }
        }

        inline void Destroy() {
            delete mPointer;
            mPointer = nullptr;
        }
    };


    template <typename T>
    class FreedScopedPointer : public PointerBase<T> {
    public:
        inline FreedScopedPointer() { }
        inline FreedScopedPointer(T* ptr) {
            mPointer = ptr;
        }

        inline ~FreedScopedPointer() {
            if (nullptr != mPointer) {
                gfl::Free(mPointer);
                mPointer = nullptr;
            }
        }

        inline void Destroy() {
            gfl::Free(mPointer);
            mPointer = nullptr;
        }

        inline void Create() {
            mPointer = new T;
        }

        inline void Create(T* ptr) {
            if (nullptr == ptr) {
                if (nullptr != mPointer) {
                    Destroy();
                }
            } else {
                mPointer = ptr;
            }
        }

        inline void Create(u8 heapID) {
            T* ptr = new (heapID) T;

            if (!ptr) {
                Destroy();
            } else {
                mPointer = ptr;
            }
        }
    };

    // temporary name
    template <typename T, void (*ReleaseFunc)(T*)>
    class CustomFreedScopedPointer : public PointerBase<T> {
    public:
        inline CustomFreedScopedPointer(T* ptr) {
            mPointer = ptr;
        }

        inline void Create(T* ptr) {
            if (ptr == nullptr) {
                Destroy();
            } else {
                mPointer = ptr;
            }
        }

        inline ~CustomFreedScopedPointer() {
            if (mPointer != nullptr) {
                ReleaseFunc(mPointer);
                mPointer = nullptr;
            }
        }

        inline void Destroy() {
            if (mPointer != nullptr) {
                ReleaseFunc(mPointer);   
                mPointer = nullptr;
            }
        }
    };
}

#endif
