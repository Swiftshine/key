#ifndef GFL_COLOR_H
#define GFL_COLOR_H

#include "types.h"


namespace gfl {

class Color {
public:
    Color()
        : r(0xFF)
        , g(0xFF)
        , b(0xFF)
        , a(0xFF)
    { }

    Color(u8 nr, u8 ng, u8 nb, u8 na)
        : r(nr)
        , g(ng)
        , b(nb)
        , a(na)
    { }

    Color(uint v)
        : val(v)
    { }

    void Interpolate(float fromWeight, float toWeight, const Color& rFrom, const Color& rTo);
    
    union {
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };

        uint val;
    };
};

}

#endif