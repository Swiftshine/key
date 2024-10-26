#ifndef FLUFF_STAGERESOURCES_H
#define FLUFF_STAGERESOURCES_H

#include "types.h"
#include "gfl/gflLinkedList.h"
#include <string>
#include "object/Gimmick.h"

class StageResources {
private:
    static StageResources* sInstance;
public:
    StageResources();
    ~StageResources();

    static inline StageResources* Instance() {
        return sInstance;
    }

    void AddGimmickName(const char*);
    void AddResourceName(const char*);
private:
    gfl::LinkedList<std::string*> mGimmickResourceNameList;
    gfl::LinkedList<std::string*> mGimmickNameList;
    gfl::LinkedList<std::string*> mCharaResourceNameList;
    gfl::LinkedList<Gimmick::GimmickBuildInfo*> mGimmickBuildInfoList;
    gfl::LinkedList<int> mGimmickIDList;
};

ASSERT_SIZE(StageResources, 0x3C);

#endif
