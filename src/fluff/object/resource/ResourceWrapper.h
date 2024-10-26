#ifndef FLUFF_RESOURCEWRAPPER_H
#define FLUFF_RESOURCEWRAPPER_H

#include "gfl/gflScnMdlWrapper.h"

// todo: find a better name for this
class ResourceWrapper {
public:
    ResourceWrapper();
    ~ResourceWrapper();
private:
    gfl::ScnMdlWrapper* mModelWrapper1;
    gfl::ScnMdlWrapper* mModelWrapper2;
    float m_8;
    float m_C;
};

#endif
