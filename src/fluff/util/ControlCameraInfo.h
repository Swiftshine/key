#ifndef FLUFF_CONTROLCAMERAINFO_H
#define FLUFF_CONTROLCAMERAINFO_H

#include <string>

class FlfGameObj;

extern "C" {
    // temporary workaround for code merging
    void fn_80788320(void*);
    int fn_807A43D0(void*);
}

// size: 0x1C
class ControlCameraInfo {
public:
    ControlCameraInfo();
    ~ControlCameraInfo();

    void SetState(FlfGameObj* object, std::string& state);

    inline void ResetCounter() {
        fn_80788320(this);
    }

    inline int GetUnk14() {
        return fn_807A43D0(this);
    }

    bool fn_803CB5E8(const char*);
    void fn_803CB458(int, const char*, int);

private:
    int m_0;
    int m_4;
    std::string mString; // @ 0x8
    int m_14;
    int mCounter;
};

#endif
