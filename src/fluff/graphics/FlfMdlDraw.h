#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"
#include "graphics/FullSortScene.h"
#include <string>

// size: 0x1C8
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
    FlfMdlDraw(FullSortScene*, const char*, int, int);
    virtual ~FlfMdlDraw();

    void LoadNURBSFromFileList();
    void fn_80023A40(int);
    void fn_800234AC(int, bool);
    void SetWoolDrawMatrix(nw4r::math::MTX34&);
    bool fn_800239CC();
    inline uint GetUnk20() {
        return m_20;
    }
    
private:
    std::string mResourcePath;
    std::string mRawFilepath;
    FullSortScene* mFullSortScene;
    uint m_20;
    STRUCT_FILL(0x1A4);
};

#endif
