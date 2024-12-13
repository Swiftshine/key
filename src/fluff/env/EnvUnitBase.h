#ifndef FLUFF_ENVUNITBASE_H
#define FLUFF_ENVUNITBASE_H

#include "env/EnvObject.h"
#include "gfl/gflResFileInfo.h"
#include <deque>

namespace env {
    class EnvUnitBase : public EnvObject {
    public:
        EnvUnitBase(gfl::Task* parentTask, const char* taskName, uint arg3);
        virtual ~EnvUnitBase();

        void RegisterResource(const char* resources, uint count);
        void ClearAll();
        bool CheckResources();
    private:
        std::deque<gfl::ResFileInfo> mResources;
    };
    
}

#endif
