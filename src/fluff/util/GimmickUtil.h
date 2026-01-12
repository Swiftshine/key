#ifndef FLUFF_GIMMICKUTIL_H
#define FLUFF_GIMMICKUTIL_H

#include "types.h"
#include "object/Gimmick.h"
#include "gfl/gflResInfo.h"
#include <string>

typedef Gimmick*(* GimmickBuildFunction)(Gimmick::GimmickBuildInfo* pBuildInfo);

namespace GimmickUtil {
    struct GimmickEntry {
        /// @note In Japanese with ShiftJIS encoding
        /* 0x0 */ const char* mDescription;
        /* 0x4 */ const char* mResourceName;
        /* 0x8 */ GimmickBuildFunction mBuildFunction;
        /* 0xC */ bool mIsCommon;
    };

    ASSERT_SIZE(GimmickEntry, 0x10);

    int GetGimmickIDByDescription(const char* pDescription);
    const char* GetResourceNameByGimmickID(int id) DONT_INLINE_CLASS;
    std::string GetResourcePathByGimmickID(int id) DONT_INLINE_CLASS;
    GimmickBuildFunction GetBuildFunctionByGimmickID(int id) DONT_INLINE_CLASS;
    bool CheckCommonByGimmickID(int id) DONT_INLINE_CLASS;
    bool IsBead(int id) DONT_INLINE_CLASS;
    int fn_80050700(int id) DONT_INLINE_CLASS;
    int fn_80050764(int arg0, int arg1) DONT_INLINE_CLASS;
    bool IsClothTurnGimmick(int id) DONT_INLINE_CLASS;
    bool fn_800507C8(int id) DONT_INLINE_CLASS;
    void GetButtonBRRES(gfl::ResFileObject& rDest) DONT_INLINE_CLASS;
    bool CheckString_hide(Gimmick::GimmickBuildInfo* pBuildInfo);
    bool CheckString_goal(Gimmick::GimmickBuildInfo* pBuildInfo);
    
    void SetString_gate_03(std::string& rString) {
        rString = "gate_03";
    }
    // not in this TU, likely doesnt belong to this namespace

    void AddGimmickName(Gimmick::GimmickBuildInfo*) DONT_INLINE_CLASS;
}

// i dont know how many entries there are yet
GimmickUtil::GimmickEntry GimmickTable[1];

#endif
