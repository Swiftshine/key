#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"

class FlfMdlDraw {
public:
    static void GetFileInfoFromArchive(gfl::ResFileInfo*& src, const char* path);
    static void GetFileInfoFromFolder(gfl::ResFileInfo*& src, const char* path);

    static inline void FromArchive(gfl::ResFileObject& src, const char* path) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromArchive(object, path);
        src = object;
    }

    static inline void FromFolder(gfl::ResFileObject& src, const char* path) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromFolder(object, path);
        src = object;
    }
    
public:
    virtual ~FlfMdlDraw();

    void fn_800234AC(bool, bool);
};

#endif
