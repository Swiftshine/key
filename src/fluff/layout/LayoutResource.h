#ifndef FLUFF_LAYOUT_LAYOUTRESOURCE_H
#define FLUFF_LAYOUT_LAYOUTRESOURCE_H

#include "gfl/gflResFileInfo.h"

namespace layout {

class LayoutResource {
public:
    static gfl::ResFileObject GetResFileObjectFromFolder(const char* pFilepath);
    static void GetResFileObjectFromFolder(gfl::ResFileObject* rDst, const char* pFilepath);
};

}

#endif
