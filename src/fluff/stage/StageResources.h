#ifndef FLUFF_STAGERESOURCES_H
#define FLUFF_STAGERESOURCES_H

#include "types.h"
#include "gfl/gflLinkedList.h"
#include <string>
#include "object/Gimmick.h"
#include "mapdata/Mapdata.h"

class StageResources {
private:
    static StageResources* sInstance;
public:
    StageResources();
    ~StageResources();

    static inline StageResources* Instance() {
        return sInstance;
    }

    void RegisterMapdataResources(Mapdata* mapdata);
    void AddResourceName(const char* name);
    void AddGimmickName(const char* name);
    void AddCharaResourceName(const char* name);
    void AddGimmickBuildInfo(Gimmick::GimmickBuildInfo* buildInfo);
    void AddResourceNameByGimmickID(int id);
    void fn_80052228();
    void fn_800522C4(uint index);
    void fn_8005234C(uint arg1);
    void fn_800524F8(const char* name, bool arg2);
    void fn_80052560(const char* name, bool arg2);
    void fn_800525C8(const char* name, bool arg2);
private:
    gfl::LinkedList<std::string*> mGimmickResourceNameList;
    gfl::LinkedList<std::string*> mGimmickNameList;
    gfl::LinkedList<std::string*> mCharaResourceNameList;
    gfl::LinkedList<Gimmick::GimmickBuildInfo*> mGimmickBuildInfoList;
    gfl::LinkedList<int> mGimmickIDList;
};

ASSERT_SIZE(StageResources, 0x3C);

#endif
