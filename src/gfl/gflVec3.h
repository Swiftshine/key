#ifndef GFL_VEC3_H
#define GFL_VEC3_H

#include <nw4r/math.h>

namespace gfl {
    struct Vec3 {
    public:
        Vec3(nw4r::math::VEC2&);
        Vec3(nw4r::math::VEC3&);
        
        Vec3(float, float, float);
        Vec3();
        inline Vec3(float val) { x = val; y = val; z = val; }
        inline ~Vec3() {}
        

        inline void operator=(float val) { x = val; y = val; z = val; }
        Vec3 operator-(Vec3& other);
        Vec3 operator+(Vec3& other);

    public:
        float x, y, z;
    };
}
#endif