#ifndef FLUFF_LAYOUT_LAYOUTRESOURCE_H
#define FLUFF_LAYOUT_LAYOUTRESOURCE_H

#include "gfl/gflResFileInfo.h"

namespace layout {

class LayoutResource {
public:
    static gfl::ResFileObject GetResFileObjectFromFolder(const char* pFilepath);
    static void GetResFileObjectFromFolder(gfl::ResFileObject* rDst, const char* pFilepath);
    
    LayoutResource();
    virtual ~LayoutResource();

    void Update();
    s32 LoadResource(const char* pResourceName);
    s32 fn_80035BC4(const char*);
    s32 RemoveResource(const char* pResourceName);
private:
    STRUCT_FILL(0x28);
};

}

#endif
