#ifndef FLUFF_STAGE_FULL_SORT_SCENE_H
#define FLUFF_STAGE_FULL_SORT_SCENE_H
#include <gfl/render/Scene.h>
#include <gfl/render/ScnMdlWrapper.h>

class FullSortScene : public gfl::Scene {
public:
    void SetModelWrapper(gfl::ScnMdlWrapper* modelWrapper);
};

#endif
