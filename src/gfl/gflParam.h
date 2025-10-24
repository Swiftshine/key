#ifndef GFL_PARAM_H
#define GFL_PARAM_H

#include <string>

#include "types.h"
#include "gflConsole.h"

namespace gfl {
    class ParamS32;
    class ParamBool;
    
    /// @brief Base class for parameter types.
    /// @note Size: `0x24`
    class Param {
    public:
        /* Constructor */
        Param(const char* pLabel);

        /* Virtual Methods */

        /* 0x08 */ virtual int vf8() = 0;
        /* 0x0C */ virtual void vfC() = 0;
        /* 0x10 */ DECL_WEAK virtual ~Param();
        /* 0x14 */ virtual void Print(Console* pConsole, uint numTabs) = 0;

        bool Matches(const char* pQuery, uint queryChecksum);
        void PrintTabs(Console* pConsole, uint count);

        /* Class Members */

        /* 0x04 */ char mLabel[32];
        /* 0x24 */ uint mChecksum;
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

    class ParamGroup : public Param {
    public:
        static bool GetGlobalBool(const char* param);
    };
}


#endif
