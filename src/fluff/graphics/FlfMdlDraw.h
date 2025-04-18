#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"
#include "graphics/FullSortScene.h"
#include <string>

// size: 0x1C8
class FlfMdlDraw {
public:
    static void GetFileInfoFromArchive(gfl::ResFileObject& object, const char* path);
    static void GetFileInfoFromFolder(gfl::ResFileObject& object, const char* path);

    static inline void FromArchive(gfl::ResFileObject& dst, const char* path) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromArchive(object, path);
        dst = object;
    }

    static inline void FromFolder(gfl::ResFileObject& dst, const char* path) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromFolder(object, path);
        dst = object;
    }
    
public:
    FlfMdlDraw(FullSortScene*, const char*, int, int);
    virtual ~FlfMdlDraw();

    void LoadNURBSFromFileList();
    void fn_80023A40(int);
    void ResetNURBSAnimation(int, bool);
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
