#ifndef GFL_PARAM_H
#define GFL_PARAM_H

#include <string>

#include "types.h"
#include "gflConsole.h"

namespace gfl {
    class ParamS32;
    class ParamBool;
    
    class Param {
    public:
        Param(const char* newLabel);

        virtual int vf8() = 0;
        virtual void vfC() = 0;
        DECL_WEAK virtual ~Param();
        virtual void Print(Console* console, uint numTabs) = 0;

        bool Matches(const char* queryLabel, uint queryChecksum);
        void PrintTabs(Console* console, uint count);
    public:
        char mLabel[32];
        uint mChecksum;
    };

    // 'A' means 'array'
    class ParamStrA : public Param {
    public:
        ParamStrA(const char* label, uint count);
        virtual ~ParamStrA();

        DECL_WEAK virtual int vf8() override;
        virtual void vfC() override;
        virtual void Print(Console* console, uint numTabs) override;

        inline uint GetCount() { return mCount; }
        inline std::string& operator[](uint index) { return mArray[index]; }
    private:
        std::string* mArray;
        uint mCount;
    };
}


#endif
