#ifndef GFL_OFFSET_H
#define GFL_OFFSET_H

#include "types.h"

namespace gfl {

template <typename T>
class Offset {
public:
    inline T* operator->() const {
        return ptr;
    }

    inline T* pointer() const {
        return ptr;
    }

    inline u32 offset() const {
        return offs;
    }

    static inline T* IncrementPointer(T* ptr) {
        ptr = reinterpret_cast<T*>(reinterpret_cast<u8*>(ptr) + 4);
        return ptr;
    }

    inline T* SetPointer(void* pBase) {
        this->ptr = reinterpret_cast<T*>(
            reinterpret_cast<u8*>(pBase) + offset()
        );

        return pointer();
    }
private:
    union {
        u32 offs;
        T* ptr;
    };
};

}

#endif
