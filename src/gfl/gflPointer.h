#ifndef GFL_POINTER_H
#define GFL_POINTER_H

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

        inline void Set(T* ptr) {
            mPointer = ptr;
        }

        inline void operator=(T* ptr) {
            mPointer = ptr;
        }

        inline bool operator==(T* other) const {
            return mPointer == other;
        }

        inline bool operator!=(T* other) const {
            return mPointer != other;
        }

        inline T* operator->() const {
            return mPointer;
        }

        operator T*() {
            return mPointer;
        }

        operator const T*() const {
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
    class Pointer : public PointerBase<T> {
    public:
        inline Pointer() { }
        inline Pointer(T* ptr) {
            mPointer = ptr;
        }

        inline ~Pointer() {
            delete mPointer;
            mPointer = nullptr;
        }

        inline void Create() {
            mPointer = new T;
        }

        inline void Create(T* ptr) {
            if (ptr == nullptr) {
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

        inline operator T*() const {
            return mPointer;
        }
    };


    template <typename T>
    class FreedPointer : public PointerBase<T> {
    public:
        inline FreedPointer() { }
        inline FreedPointer(T* ptr) {
            mPointer = ptr;
        }

        inline ~FreedPointer() {
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
    
    template <typename T, void (*ReleaseFunc)(T*)>
    class ReleasedPointer : public PointerBase<T> {
    public:
        inline ReleasedPointer() { }
        
        inline ReleasedPointer(T* ptr) {
            mPointer = ptr;
        }

        inline void Create(T* ptr) {
            if (ptr == nullptr) {
                Destroy();
            } else {
                mPointer = ptr;
            }
        }

        inline ~ReleasedPointer() {
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
