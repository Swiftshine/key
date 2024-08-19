#ifndef GFL_VECTOR_H
#define GFL_VECTOR_H

#include <gfl/gfl_types.h>

namespace gfl {
    struct VectorIterator {
        void* mpData;
    };
    
    class Vector {
    public:
        inline Vector() { }
        ~Vector();
        void fn_800187d0(u32 arg1);
        void Resize(u32 newsize);
    public:
        VectorIterator* mpIterators;
        u32 mCount;
        u32 mCapacity;
    };
}

#endif
