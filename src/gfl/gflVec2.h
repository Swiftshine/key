#ifndef GFL_VEC2_H
#define GFL_VEC2_H

#include <nw4r/math/math_types.h>
#include "types.h"

namespace gfl {
    struct Vec2 : public nw4r::math::VEC2 {
        static const Vec2 Zero;

        Vec2();

        Vec2(float nx, float ny) {
            x = nx;
            y = ny;
        }

        inline Vec2 operator+(const Vec2& rhs) const {
            return Vec2(x + rhs.x, y + rhs.y);
        }

        inline Vec2 operator-(const Vec2& rhs) const {
            return Vec2(x - rhs.x, y - rhs.y);
        }

        inline Vec2 operator*(float scalar) const {
            return Vec2(x * scalar, y * scalar);
        }

        inline void operator=(float val) {
            x = val;
            y = val;
        }

        inline void operator=(const nw4r::math::VEC2& rOther) {
            x = rOther.x;
            y = rOther.y;
        }
        

        static bool Sanitize(nw4r::math::VEC2& rVec);
    };
}

#endif
