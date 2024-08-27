// add header guards later

#include "gflResInfo.h"

namespace gfl {
    class ResFileInfo : public ResInfo {
    public:
        
    };


    class ResArchivedFileInfo : public ResInfo {
    public:
        virtual ~ResArchivedFileInfo();
        // Thunk to non-virtual GetData()
        virtual void* GetData_thunk();
        DECL_WEAK size_t GetDataSize();
        // This doesn't do anything useful; this function is (presumably) never called by the game
        virtual int Recurse();
    public:

    };
}