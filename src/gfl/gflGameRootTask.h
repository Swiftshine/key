#ifndef GFL_GAMEROOTTASK_H
#define GFL_GAMEROOTTASK_H

#include "gflTask.h"

namespace gfl {

class GameRootTask : public Task {
public:
    static GameRootTask* sInstance;
    static inline GameRootTask* Instance() {
        return sInstance;
    }
};
}

#endif
