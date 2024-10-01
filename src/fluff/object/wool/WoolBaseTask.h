#ifndef FLUFF_WOOLBASETASK_H
#define FLUFF_WOOLBASETASK_H

#include "gfl/gflTask.h"
#include "object/SpringBase.h"
#include "graphics/FullSortScene.h"

class WoolBaseMdl;

// size: 0x1A4
class WoolBaseTask : public SpringBase {
public:
    WoolBaseTask(u32 arg1, gfl::Task* task, FullSortScene* scene, int** arg4, const char* woolColorName, const char* arg6, u32 arg7, const char* arg8);
    virtual ~WoolBaseTask();
    
    /* no overrides */
private:
    STRUCT_FILL((0x1A4 - 0x4) - sizeof(SpringBase));
    WoolBaseMdl* mModel;
};

ASSERT_SIZE(WoolBaseTask, 0x1A4);

#endif
