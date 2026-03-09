#ifndef FLUFF_GFL_ACCESSORS_H
#define FLUFF_GFL_ACCESSORS_H

#include "gfl/gflResFileInfo.h"

namespace fluff {
    // necessary because the functionality of these functions is duplicated for use for certain TUs
    gfl::ResFileObject GetResFileObjectFromArchive(const char* pFilepath);
    gfl::ResFileObject GetResFileObjectFromFolder(const char* pFilepath);
    gfl::ResFileObject GetResFileObjectFromFolder(char pFilepath[] /* not const for the sake of having different symbols */);
    void GetResFileObjectFromFolder(gfl::ResFileObject& dst, const char* pFilepath);
}

#endif
