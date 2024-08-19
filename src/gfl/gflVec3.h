#ifndef GFL_VEC3_h
#define GFL_VEC3_H


namespace gfl {
    struct Vec3 {
    public:
        Vec3(float, float, float);
        Vec3();

        inline ~Vec3() {}
        
        Vec3 operator-(Vec3& other);
        Vec3 operator+(Vec3& other);

    public:
        float x, y, z;
    };
}
#endif