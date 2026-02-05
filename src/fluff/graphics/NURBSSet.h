#ifndef FLUFF_NURBSSET_H
#define FLUFF_NURBSSET_H

#include "types.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/MNEB.h"

// size unk
class NURBSSet {
public:
    void Set(float, uint count, bool, const gfl::ResFileObject& rResFileObject);
    NURBSObject* GetObject(uint index) const;
    /* Class Members */

    /* 0x00 */ STRUCT_FILL(0x14);
    /* 0x14 */ MNEB::DemoDataBlock* mEntry;
};

#endif
