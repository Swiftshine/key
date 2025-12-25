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
        /* 0x00 */ float m_0;
        /* 0x04 */ float m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ float m_C;
        /* 0x10 */ float m_10;
        /* 0x14 */ float m_14;
        /* 0x18 */ int m_18;
        /* 0x1C */ int m_1C;
        /* 0x20 */ int m_20;
        /* 0x24 */ int m_24;
        /* 0x28 */ bool m_28;
        /* 0x2C */ int m_2C;
        /* 0x30 */ int m_30;
        /* 0x34 */ uint m_34;
        /* 0x38 */ uint m_38;
        /* 0x3C */ int m_3C;
        /* 0x40 */ bool m_40;
        /* 0x41 */ bool m_41;
        /* 0x44 */ int m_44;
        /* 0x48 */ int m_48;
        /* 0x4C */ int m_4C;
    };
    
    /* Constructor */

    WoolBaseTask(
        WoolBuildInfo* pWoolBuildInfo,
        gfl::Task* pTask,
        FullSortScene* pArg4,
        int** arg4,
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
