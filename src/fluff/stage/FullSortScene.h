#ifndef FLUFF_FULLSORTSCENE_H
#define FLUFF_FULLSORTSCENE_H

#include "gfl/gflScene.h"
#include "gfl/gflScnMdlWrapper.h"

class FullSortScene : public gfl::Scene {
public:
    void SetModelWrapper(gfl::ScnMdlWrapper* modelWrapper);
};

#endif
