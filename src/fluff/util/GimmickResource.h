#ifndef FLUFF_GIMMICKRESOURCE_H
#define FLUFF_GIMMICKRESOURCE_H

#include "object/Gimmick.h"
#include "gfl/gflLinkedList.h"
#include <string>

/// @brief Used for keeping track of gimmicks that use a particular resource.
/// @note Size: `0x1C`
class GimmickResource {
public:
    /* Constructor + Destructor */

    GimmickResource(const char* pResName);
    ~GimmickResource();

    /* Class Methods */

    void RegisterGimmick(Gimmick* pGmk);
    void Clear();

    /* Class Members */
    
    /* 0x00 */ std::string mResourceName;
    /* 0x0C */ bool m_C;
    /* 0x10 */ gfl::LinkedList<FlfHandle> mGimmickHandles;
};

#endif
