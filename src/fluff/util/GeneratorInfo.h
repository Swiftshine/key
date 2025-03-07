#ifndef FLUFF_GENERATORINFO_H
#define FLUFF_GENERATORINFO_H

#include <string>

class FlfGameObj;

extern "C" {
    // temporary workaround for code merging
    void fn_80788320(void*);
    int fn_807A43D0(void*);
}

// size: 0x1C
class GeneratorInfo {
public:
    GeneratorInfo();
    ~GeneratorInfo();

    void SetState(FlfGameObj* object, std::string& state);

    inline void ResetCounter() {
        fn_80788320(this);
    }

    inline int GetUnk14() {
        return fn_807A43D0(this);
    }

    bool fn_803CB5E8(const char*);
    void fn_803CB458(int, const char*, int);
    uint fn_803CB4B4();
private:
    int m_0;
    int m_4;
    std::string mAssociatedTag; // @ 0x8
    int m_14;
    int mCounter;
};

#endif
