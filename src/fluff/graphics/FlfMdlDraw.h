#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"

class FlfMdlDraw {
public:
    static void GetFileInfoFromArchive(gfl::ResFileInfo*& src, const char* path);
    static void GetFileInfoFromFolder(gfl::ResFileInfo*& src, const char* path);

    static inline void FromArchive(gfl::ResFileInfo*& src, const char* path) {
        gfl::ResFileInfo* temp;


        gfl::ResFileInfo::ConfigureFromArchive(&temp, path);

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
    static inline void FromFolder(gfl::ResFileInfo*& src, const char* path) {
        gfl::ResFileInfo* temp;

        gfl::ResFileInfo::ConfigureFromFolder(&temp, path);

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
