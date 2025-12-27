#ifndef GFL_PARAM_H
#define GFL_PARAM_H

#include <string>

#include "types.h"
#include "gflConsole.h"

namespace gfl {
    class ParamStr;
    class ParamS32;
    class ParamF32;
    class ParamBool;
    class ParamS32A;
    class ParamF32A;
    class ParamStrA;
    class ParamBoolA;
    
    /// @brief Base class for parameter types.
    /// @note Size: `0x24`
    class Param {
    public:
        
        Param(const char* pLabel);

        /* Virtual Methods */

        /* 0x08 */ DECL_WEAK virtual int vf8() = 0;
        /* 0x0C */ virtual void vfC() = 0;
        /* 0x10 */ DECL_WEAK virtual ~Param();
        /* 0x14 */ virtual void Print(Console* pConsole, uint numTabs) = 0;

        bool Matches(const char* pQuery, uint queryChecksum);
        void PrintTabs(Console* pConsole, uint count);

        /* Utility Inlines */
        
        inline ParamF32* ToParamF32() {
            return (ParamF32*)this;
        }

        /* Class Members */

        /* 0x04 */ char mLabel[32];
        /* 0x24 */ uint mChecksum;
    };

    class ParamS32 : public Param {
    public:
        ParamS32(const char* pLabel);

        /* Virtual Methods */

        /* 0x08 */ DECL_WEAK virtual int vf8();
        /* 0x0C */ DONT_OPTIMIZE virtual void vfC();
        /* 0x10 */ DECL_WEAK virtual ~ParamS32();
        /* 0x14 */ DONT_OPTIMIZE virtual void Print(Console* pConsole, uint numTabs);

        /* Class Members */

        /* 0x28 */ int mValue;
    };

    class ParamF32 : public Param {
    public:
        ParamF32(const char* pLabel);

        /* Virtual Methods */

        /* 0x08 */ DECL_WEAK virtual int vf8();
        /* 0x0C */ DONT_OPTIMIZE virtual void vfC();
        /* 0x10 */ DECL_WEAK virtual ~ParamF32();
        /* 0x14 */ DONT_OPTIMIZE virtual void Print(Console* pConsole, uint numTabs);

        /* Class Methods */

        /* 0x28 */ float mValue;
    };


    class ParamBool : public Param {
    public:
        ParamBool(const char* pLabel);

        /* Virtual Methods */
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
        static Param* GetGlobalParam(const char* pName);
        static bool GetGlobalBool(const char* pName);
        static ParamGroup* GetGlobalParamGroup(const char* pName);

        ParamS32* GetS32Param(const char*);
        ParamF32* GetF32Param(const char*);
    };
}


#endif
