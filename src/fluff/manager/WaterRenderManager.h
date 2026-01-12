#ifndef FLUFF_WATERRENDERMANAGER_H
#define FLUFF_WATERRENDERMANAGER_H

#include <list>
#include "types.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/GmkWoolWaterRender.h"

/// @note Size: `0x18`
class WaterRenderManager {
public:
    WaterRenderManager();
    ~WaterRenderManager();
    
    /* Class Methods */
    void Update(bool shouldUpdate);
    
    /* 0x0 */ std::list<GmkWoolWaterRender*> mWaterRenderers;
    /* 0xC */ std::list<FlfMdlDraw*> mFlfMdlDraws;
};


#endif