#ifndef FLUFF_WOOLBASETASK_H
#define FLUFF_WOOLBASETASK_H

#include "gfl/gflTask.h"
#include "object/SpringBase.h"
#include "graphics/FullSortScene.h"

class WoolBaseMdl;

// size: 0x1A4
class WoolBaseTask : public SpringBase {
public:
    // size: 0x50
    struct WoolBuildInfo {
        float m_0;
        float m_4;
        float m_8;
        float m_C;
        float m_10;
        float m_14;
        int m_18;
        int m_1C;
        int m_20;
        int m_24;
        bool m_28;
        int m_2C;
        int m_30;
        int m_34;
        int m_38;
        int m_3C;
        bool m_40;
        bool m_41;
        int m_44;
        int m_48;
        int m_4C;
    };
    
public:
    WoolBaseTask(WoolBuildInfo* wBuildInfo, gfl::Task* task, FullSortScene* scene, int** arg4, const char* woolColorName, const char* arg6, u32 arg7, const char* arg8);
    virtual ~WoolBaseTask();
    
    /* no overrides */

protected:
    WoolBuildInfo mWoolBuildInfo;
    WoolBaseMdl* mModel;
};

ASSERT_SIZE(WoolBaseTask, 0x1A4);

#endif
