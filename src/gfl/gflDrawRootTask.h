#ifndef GFL_DRAWROOTTASK_H
#define GFL_DRAWROOTTASK_H

#include "gflTask.h"

namespace gfl {

class DrawRootTask : public Task {
public:
    static DrawRootTask* sInstance;
    static inline DrawRootTask* Instance() {
        return sInstance;
    }
};

}

#endif
