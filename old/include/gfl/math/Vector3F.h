#ifndef GFL_VECTOR3F_H
#define GFL_VECTOR3F_H

namespace gfl {
    struct Vec3 {
        Vec3(float, float, float);

        Vec3();

        Vec3 operator-(Vec3& other);

        Vec3 operator+(Vec3& other);
        
        float x, y, z;
    };
    
}

#endif
