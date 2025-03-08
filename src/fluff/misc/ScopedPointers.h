#ifndef FLUFF_SCOPEDPOINTERS_H
#define FLUFF_SCOPEDPOINTERS_H

#include "types.h"
#include <nw4r/g3d.h>
#include <nw4r/g3d/g3d_obj.h>

#include "gfl/gflPointer.h"

template <typename T>
class G3dObjPointer : public gfl::PointerBase<T> {
public:
    inline G3dObjPointer() { }
    inline G3dObjPointer(T* ptr) {
        mPointer = ptr;
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

#endif
