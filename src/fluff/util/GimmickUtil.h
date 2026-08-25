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

    const char* GetResourceNameByGimmickID(s32 id) DONT_INLINE_CLASS;
    std::string GetResourcePathByGimmickID(s32 id) DONT_INLINE_CLASS;
    GimmickBuildFunction GetBuildFunctionByGimmickID(s32 id) DONT_INLINE_CLASS;
    bool CheckCommonByGimmickID(s32 id) DONT_INLINE_CLASS;
    bool IsBead(s32 id) DONT_INLINE_CLASS;
    s32 fn_80050700(s32 id) DONT_INLINE_CLASS;
    s32 fn_80050764(s32 arg0, s32 arg1) DONT_INLINE_CLASS;
    bool IsClothTurnGimmick(s32 id) DONT_INLINE_CLASS;
    bool fn_800507C8(s32 id) DONT_INLINE_CLASS;
    void GetButtonBRRES(gfl::ResFileObject& rDest) DONT_INLINE_CLASS;
    s32 GetGimmickIDByCommonGimmickName(const char* pName);
    // these are probably actually just defined on a TU by TU basis
    // rather than being part of the GimmickUtil namespace
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
