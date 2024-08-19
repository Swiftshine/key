#ifndef GFL_ARRAY_H
#define GFL_ARRAY_H

#include <gfl/gfl_types.h>
#include <gfl/mem/mem.h>

namespace gfl {

    template <typename T>
    class SimpleArray {
    public:
        inline SimpleArray() { }
        
        inline ~SimpleArray() {
            delete[] mArray;
            mArray = nullptr;
        }

        inline void Create(u32 len) {
            T* temp = new (gfl::mem::HeapID::Work) T[len];

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

        inline T* get() { return mArray; }
    private:
        T* mArray;
    };
}

#endif
