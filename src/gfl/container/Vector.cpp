#include <gfl/container/Vector.h>
#include <gfl/mem/mem.h>

using namespace gfl;


Vector::~Vector() {
    if (mpIterators) {
        mCount = 0;
        delete mpIterators;
    }
}

void Vector::fn_800187d0(u32 arg1) {
    if (0 != arg1) {
        Resize(arg1);
        memset(mpIterators + mCount, 0, arg1 << 2 /* multiply by 4 */);
        mCount = mCount + arg1;
    }
}

void Vector::Resize(u32 newsize) {
    if (newsize > 0x3FFFFFFF) {
        // throw length error
    }

    VectorIterator* newArr = new (newsize << 2);
    if (!newArr) {
        // fprintf("Memory allocation error");
        // abort();
    }
    mpIterators = newArr;
    mCapacity = newsize;
}
