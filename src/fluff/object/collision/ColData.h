#ifndef FLUFF_COLDATA_H
#define FLUFF_COLDATA_H

#include "types.h"
#include "object/collision/Colbin.h"
#include "object/collision/KdTreeData.h"

class ColData : public KdTreeData {
public:
    inline ColData* GetNext() {
        return mNext;
    }

    inline void SetNext(ColData* next) {
        mNext = next;
    }

protected:
    ColData* mNext;
    uint m_C;
    uint m_10;
    uint mNumEntries;
    uint mEntryOffset;
    uint mFooterOffset;
};

#endif
