#ifndef GFL_REFCOUNTER_H
#define GFL_REFCOUNTER_H

#include "types.h"

namespace gfl {

    class RefCounter {
    public:
        /* Class Methods */

        inline void IncrementRefCount() {
            mRefCount++;
        }

        inline operator u16() const {
            return mRefCount;
        }

        /* Class Members */
    private:
        /* 0x0 */ u16 mRefCount;
    };
}

#endif