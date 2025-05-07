#ifndef FLUFF_NURBSSET_H
#define FLUFF_NURBSSET_H

#include "types.h"
#include "util/NURBSStructures.h"

// size unk
class NURBSSet {
public:
    inline NURBSStruct1* GetUnk14() {
        return m_14;
    }
private:
    STRUCT_FILL(0x14);
    NURBSStruct1* m_14;
};

#endif