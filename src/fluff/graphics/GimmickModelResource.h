#ifndef FLUFF_GIMMICKMODELRESOURCE_H
#define FLUFF_GIMMICKMODELRESOURCE_H

#include "types.h"
#include "gfl/gflVec2.h"

class Gimmick;

/// @note Size: `0x38`
class GimmickModelResource {
public:
    GimmickModelResource();
    DECL_WEAK ~GimmickModelResource();

    /* Class Members */
    const char* mBRRESPath;
    const char* mResourceName;
    int m_8;
    bool m_C;
    gfl::Vec2 m_10;
    Gimmick* mOwner;
    MTX34* mOwnerMatrix;
    bool m_20;
    bool m_21;
    float m_24;
    int mFullSortSceneID;
    float mZOrder;
    bool m_30;
    bool m_31;
    int m_34;
};

#endif