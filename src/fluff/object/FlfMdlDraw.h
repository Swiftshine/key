#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"

class FlfMdlDraw {
public:
    static void GetFileInfoFromArchive(gfl::ResInfo** out, const char* path);
    static void GetFileInfoFromFolder(gfl::ResInfo** out, const char* path);
};

#endif