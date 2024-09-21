#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"

class FlfMdlDraw {
public:
    static void GetFileInfoFromArchive(gfl::ResInfo** out, const char* path);
    static void GetFileInfoFromFolder(gfl::ResInfo** out, const char* path);

    static inline void FromArchive(gfl::ResFileInfo*& src, const char* path) {
        gfl::ResFileInfo* temp;

        GetFileInfoFromArchive((gfl::ResInfo**)(&temp), path);

        if (&src != &temp) {
            if (nullptr != src) {
                src->Destroy();
            }

            src = temp;

            if (nullptr != src) {
                src->IncrementLevel();
            }
        }


        if (nullptr != temp) {
            temp->Destroy();
        }
    }
    
};

#endif
