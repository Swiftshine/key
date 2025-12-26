#ifndef FLUFF_SCOPEDPOINTERS_H
#define FLUFF_SCOPEDPOINTERS_H

#include "types.h"
#include <nw4r/g3d/g3d_obj.h>

#include "gfl/gflPointer.h"

template <typename T>
class G3dObjPointer : public gfl::PointerBase<T> {
public:
    inline G3dObjPointer() { }
    
    inline G3dObjPointer(T* ptr) {
        mPointer = ptr;
    }

    inline void Create(T* ptr) {
        if (ptr == nullptr) {
            Destroy();
        } else {
            mPointer = ptr;
        }
    }

    inline ~G3dObjPointer() {
        if (nullptr != mPointer) {
            reinterpret_cast<nw4r::g3d::G3dObj*>(mPointer)->Destroy();
            mPointer = nullptr;
        }
    }

    inline void Destroy() {
        if (nullptr != mPointer) {
            reinterpret_cast<nw4r::g3d::G3dObj*>(mPointer)->Destroy();
            mPointer = nullptr;
        }
    }
};

// calls some method at vtable + 0xC, but it's not a dtor
// if you have to use this, it's probably the result of some
// unused field getting cut
class DummyPointer_C : public gfl::PointerBase<pvd8_t> {
public:
    inline DummyPointer_C(pvd8_t* p) {
        mPointer = p;
    }

    ~DummyPointer_C() {
        if (mPointer != nullptr) {
            mPointer->DummyC();
        }
    }
};

#endif
