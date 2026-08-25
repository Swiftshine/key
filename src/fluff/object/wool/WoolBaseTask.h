#ifndef FLUFF_WOOLBASETASK_H
#define FLUFF_WOOLBASETASK_H

#include "gfl/gflTask.h"
#include "object/SpringBase.h"
#include "graphics/FullSortScene.h"

class WoolBaseMdl;

/// @note Size: `0x1A4`
class WoolBaseTask : public SpringBase {
public:
    /* Structures */

    /// @note Size: `0x50`
    struct WoolBuildInfo {
        /* 0x00 */ f32 m_0;
        /* 0x04 */ f32 m_4;
        /* 0x08 */ f32 m_8;
        /* 0x0C */ f32 m_C;
        /* 0x10 */ f32 m_10;
        /* 0x14 */ f32 m_14;
        /* 0x18 */ s32 m_18;
        /* 0x1C */ s32 m_1C;
        /* 0x20 */ s32 m_20;
        /* 0x24 */ s32 m_24;
        /* 0x28 */ bool m_28;
        /* 0x2C */ s32 m_2C;
        /* 0x30 */ s32 m_30;
        /* 0x34 */ u32 m_34;
        /* 0x38 */ u32 m_38;
        /* 0x3C */ s32 m_3C;
        /* 0x40 */ bool m_40;
        /* 0x41 */ bool m_41;
        /* 0x44 */ s32 m_44;
        /* 0x48 */ s32 m_48;
        /* 0x4C */ s32 m_4C;
    };
    
    

    WoolBaseTask(
        WoolBuildInfo* pWoolBuildInfo,
        gfl::Task* pTask,
        FullSortScene* pArg4,
        s32** arg4,
        const char* pWoolColorName,
        const char* pArg6,
        u32 arg7,
        const char* pArg8
    );
    
    /* Virtual Methods */

    /* 0x08 */ virtual ~WoolBaseTask();

    /* Class Members */

    /* 0x150 */ WoolBuildInfo mWoolBuildInfo;
    /* 0x1A0 */ WoolBaseMdl* mModel;
};

ASSERT_SIZE(WoolBaseTask, 0x1A4);

#endif
