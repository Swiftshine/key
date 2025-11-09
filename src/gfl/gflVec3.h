#ifndef GFL_VEC3_H
#define GFL_VEC3_H

#include <nw4r/math.h>

namespace gfl {
    struct Vec3 {
    public:
        static Vec3 Zero;
        static Vec3 One;
    public:
        Vec3(float, nw4r::math::VEC2&);
        Vec3(nw4r::math::VEC2&);
        Vec3(nw4r::math::VEC3&);
        
        inline Vec3(const Vec3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        Vec3(float, float, float);
        Vec3();

        inline Vec3(float val) { x = val; y = val; z = val; }
        inline ~Vec3() {}
        

        inline void operator=(float val) { x = val; y = val; z = val; }
        inline void operator=(Vec3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        void operator=(nw4r::math::VEC2& other);
        Vec3 operator-(Vec3& other);
        Vec3 operator+(Vec3& other);

        inline operator nw4r::math::VEC3*() {
            return reinterpret_cast<nw4r::math::VEC3*>(this);
        }

        inline operator nw4r::math::VEC3&() {
            return *reinterpret_cast<nw4r::math::VEC3*>(this);
        }
    public:
        float x, y, z;
    };
}
#endif
