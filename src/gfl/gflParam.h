#ifndef GFL_PARAM_H
#define GFL_PARAM_H

#include "types.h"
#include "gflConsole.h"

namespace gfl {
    class Param {
    public:
        Param(const char* newLabel);

        virtual void vf8() = 0;
        virtual void vfC() = 0;
        DECL_WEAK virtual ~Param();
        // virtual void vf14() = 0;

        bool Matches(const char* queryLabel, uint queryChecksum);
        void PrintTabs(Console* console, uint count);
    public:
        char mLabel[32];
        uint mChecksum;

    };
}


#endif