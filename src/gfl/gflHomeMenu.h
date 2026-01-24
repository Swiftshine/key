#ifndef GFL_HOMEMENU_H
#define GFL_HOMEMENU_H

#include "types.h"

namespace gfl {

/// @note Size: `0x498`
class HomeMenu {
public:
    static HomeMenu* sInstance;
    static HomeMenu* GetInstance();

    virtual ~HomeMenu();

    inline void SetUnk4(bool b) {
        m_4 = !b;
    }
    
    bool m_4;
    PAD(3);
    STRUCT_FILL(0x490);
};

}

#endif