#ifndef FLUFF_GIMMICKUTIL_H
#define FLUFF_GIMMICKUTIL_H

#include "types.h"
#include "object/Gimmick.h"
#include "gfl/gflResInfo.h"
#include <string>

typedef Gimmick*(* GimmickBuildFunction)(Gimmick::GimmickBuildInfo* info);


namespace GimmickUtil {
    class GimmickEntry {
    public:
        const char* GetDescription() { return mDescription; }
        const char* GetResourceName() { return mResourceName; }
        GimmickBuildFunction GetBuildFunction() { return mBuildFunction; }
        bool IsCommon() { return mIsCommon; }
    private:
        const char* mDescription; // in japanese, ShiftJIS
        const char* mResourceName;
        GimmickBuildFunction mBuildFunction;
        bool mIsCommon;
    };

    ASSERT_SIZE(GimmickEntry, 0x10);


    int GetGimmickIDByDescription(const char* description);
    const char* GetResourceNameByGimmickID(int id) DONT_INLINE_CLASS;
    std::string GetResourcePathByGimmickID(int id) DONT_INLINE_CLASS;
    GimmickBuildFunction GetBuildFunctionByGimmickID(int id) DONT_INLINE_CLASS;
    bool CheckCommonByGimmickID(int id) DONT_INLINE_CLASS;
    bool IsBead(int id) DONT_INLINE_CLASS;
    int fn_80050700(int id) DONT_INLINE_CLASS;
    int fn_80050764(int arg0, int arg1) DONT_INLINE_CLASS;
    bool IsClothTurnGimmick(int id) DONT_INLINE_CLASS;
    bool fn_800507C8(int id) DONT_INLINE_CLASS;
    void GetButtonBRRES(gfl::ResInfo** dest) DONT_INLINE_CLASS;

    // not in this TU, likely doesnt belong to this namespace

    void AddGimmickName(Gimmick::GimmickBuildInfo*) DONT_INLINE_CLASS;
}

// i dont know how many entries there are yet
GimmickUtil::GimmickEntry GimmickTable[1];

#endif
