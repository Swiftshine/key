#ifndef FLUFF_ENVUNITBASE_H
#define FLUFF_ENVUNITBASE_H

#include "env/EnvObject.h"
#include "gfl/gflResFileInfo.h"
#include <deque>

namespace env {
    class EnvUnitBase : public EnvObject {
    public:
        /* Constructor */

        EnvUnitBase(gfl::Task* pParentTask, const char* pTaskName, uint arg3);

        /* Virtual Methods */

        /* 0x08 */ virtual ~EnvUnitBase();

        /* Class Methods */

        void RegisterResource(const char* pResourceName, uint count);
        void ClearAll();
        bool CheckResources();

        /* Class Members */
        
        /* 0x04 */ std::deque<gfl::ResFileInfo> mResources;
    };
    
}

#endif
