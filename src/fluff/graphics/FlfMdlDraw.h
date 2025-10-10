#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include "gfl/gflResFileInfo.h"
#include "graphics/FullSortScene.h"
#include "graphics/NURBSSet.h"
#include <string>

// size: 0x1C8
class FlfMdlDraw {
public:
    /* Constructor */

    FlfMdlDraw(FullSortScene*, const char*, int, int);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfMdlDraw();

    /* Class Methods */
    void LoadNURBSFromFileList();
    void SetVisibility(bool visible);
    void ResetNURBSAnimation(int, bool);
    void SetWoolDrawMatrix(nw4r::math::MTX34&);
    bool fn_800239CC();
    void fn_80023D38();
    void SetUpdateRate(float rate);
    int SetFullSortScene(FullSortScene* pFullSortScene);
    void fn_80023B24(float);
    bool IsAnimationDone();
    float GetCurrentFrame();
    float GetEndFrame();
    void SetCurrentNURBSFrame(float);
    gfl::ScnMdlWrapper* GetNURBSAnimWrapperModelWrapper();
    NURBSSet* GetNURBSAnimWrapperNURBSSet();

    inline void SetCurrentFrameInt(int value) {
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x60) = value;
    }

    inline int GetCurrentFrameInt() {
        return *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x60);
    }

    /* Static Methods */

    static void GetFileInfoFromArchive(gfl::ResFileObject& rObject, const char* pFilepath);
    static void GetFileInfoFromFolder(gfl::ResFileObject& rObject, const char* pFilepath);

    static inline void FromArchive(gfl::ResFileObject& rObject, const char* pFilepath) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromArchive(object, pFilepath);
        rObject = object;
    }

    static inline void FromFolder(gfl::ResFileObject& rObject, const char* rFilepath) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromFolder(object, rFilepath);
        rObject = object;
    }

    
    /* Class Members */

    /* 0x04 */ std::string mResourcePath;
    /* 0x10 */ std::string mRawFilepath;
    /* 0x1C */ FullSortScene* mFullSortScene;
    /* 0x20 */ uint m_20;
    /* 0x24 */ STRUCT_FILL(0x1A4);
};

#endif
