#ifndef FLUFF_GENERATORINFO_H
#define FLUFF_GENERATORINFO_H

#include <string>

class FlfGameObj;

extern "C" {
    // temporary workaround for code merging
    void fn_80788320(void*);
    int fn_807A43D0(void*);
}

/// @note Size: `0x1C`
class GeneratorInfo {
public:
    

    GeneratorInfo();
    ~GeneratorInfo();

    /* Class Methods */

    void SetState(FlfGameObj* object, std::string& state);

    DECL_WEAK void ResetCounter();

    // inline void ResetCounter() {
    //     fn_80788320(this);
    // }

    inline int GetUnk14() {
        return fn_807A43D0(this);
    }

    bool fn_803CB5E8(const char*);
    void fn_803CB458(int, const char*, int);
    uint fn_803CB4B4();

    /* Class Members */

    /* 0x00 */ int m_0;
    /* 0x04 */ int m_4;
    /* 0x08 */ std::string mAssociatedTag;
    /* 0x14 */ int m_14;
    /* 0x18 */ int mCounter;
};

#endif
