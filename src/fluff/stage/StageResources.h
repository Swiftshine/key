#ifndef FLUFF_STAGERESOURCES_H
#define FLUFF_STAGERESOURCES_H

#include "types.h"
#include "gfl/gflLinkedList.h"
#include <string>
#include "object/Gimmick.h"

class StageResources {
public:
    StageResources();
    ~StageResources();
private:
    gfl::LinkedList<std::string*> mResourceNameList;
    gfl::LinkedList<std::string*> mGimmickNameList;
    gfl::LinkedList<placeholder_t> m_18;
    gfl::LinkedList<Gimmick::GimmickBuildInfo*> mGimmickBuildInfoList;
    gfl::LinkedList<placeholder_t> m_30;
};

ASSERT_SIZE(StageResources, 0x3C);

#endif
