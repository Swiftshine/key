#ifndef GFL_VEC3_H
#define GFL_VEC3_H

#include <nw4r/math.h>

namespace gfl {
    struct Vec2;

    struct Vec3 : public nw4r::math::VEC3 {
        typedef nw4r::math::VEC3 Base;

        static inline float DotProduct1(register const Vec3* pA, register const Vec3* pB) {
            register float dot;
            register float work0, work3, work2, work1;
        
            // clang-format off
            asm {
                // YZ product
                psq_l  work0, Vec3.y(pA), 0, 0
                psq_l  work1, Vec3.y(pB), 0, 0
                ps_mul work0, work0, work1
                
                // X product + YZ product
                psq_l   work3, Vec3.x(pA), 1, 0
                psq_l   work2, Vec3.x(pB), 1, 0
                ps_madd work1, work3, work2, work0
                
                // Dot product
                ps_sum0 dot, work1, work0, work0
            }
            // clang-format on
        
            return dot;
        }

        // swapping around values is necessary for a function to match
        static inline float DotProduct2(register const Vec3* pA, register const Vec3* pB) {
            register float dot;
            register float work3, work2, work1, work0;
            
            // clang-format off
            asm {
                // YZ product
                psq_l  work0, Vec3.y(pA), 0, 0
                psq_l  work1, Vec3.y(pB), 0, 0
                ps_mul work0, work0, work1
                
                // X product + YZ product
                psq_l   work3, Vec3.x(pA), 1, 0
                psq_l   work2, Vec3.x(pB), 1, 0
                ps_madd work1, work3, work2, work0
                
                // Dot product
                ps_sum0 dot, work1, work0, work0
            }
            // clang-format on
        
            return dot;
        }

        static inline float FloatAbs(float f) {
            return f < 0.0f ? -f : f;
        }
    public:
        static Vec3 Zero;
        static Vec3 One;
    public:
        /* Constructors + Destructor */

        Vec3() { }

        Vec3(float, float, float);
        Vec3(float, nw4r::math::VEC2&);
        Vec3(const nw4r::math::VEC2&);
        Vec3(const Vec2&);
        
        inline Vec3(const Base& rOther) {
            x = rOther.x;
            y = rOther.y;
            z = rOther.z;
        }
        
        inline Vec3(const Vec3& rOther) {
            x = rOther.x;
            y = rOther.y;
            z = rOther.z;
        }

    
        inline Vec3(float val) {
            x = val;
            y = val;
            z = val;
        }
        
        /* Operators */

        inline void operator=(const Base& rOther) {
            x = rOther.x;
            y = rOther.y;
            z = rOther.z;
        }
        
        inline void operator=(float val) {
            x = val;
            y = val;
            z = val;
        }

        inline Vec3 operator-() const {
            Vec3 v;
            v.x = -x;
            v.y = -y;
            v.z = -z;
            return v;
        }
        
        
        void operator=(const Vec2& other);

        // Vec3 operator+(const Base& rhs) const;
        Vec3 operator+(const Vec3& other) const;

        // Vec3 operator-(const Base& rhs) const;
        Vec3 operator-(const Vec3& other) const;

        Vec3 operator*(float scalar) const;

        inline void operator+=(const Base& rhs) {
            VEC3Add(this, this, &rhs);
        }

        inline void operator*=(float scalar) {
            VEC3Scale(this, this, scalar);
        }

        inline Vec3 operator+(const Vec3& rhs) {
            Vec3 v(0);
            VEC3Add(&v, this, &rhs);
            return v;
        }

        inline operator nw4r::math::VEC3*() {
            return reinterpret_cast<nw4r::math::VEC3*>(this);
        }

        inline operator const nw4r::math::VEC3*() const {
            return reinterpret_cast<const nw4r::math::VEC3*>(this);
        }

        inline operator nw4r::math::VEC3&() {
            return *reinterpret_cast<nw4r::math::VEC3*>(this);
        }
        inline operator const nw4r::math::VEC3&() const {
            return *reinterpret_cast<const nw4r::math::VEC3*>(this);
        }
        

        /* Class Methods */

        static inline float AngleRad(const Vec3& lhs, const Vec3& rhs) {
            float angle = VEC3Dot(&lhs, &rhs) / (VEC3Len(&lhs) * VEC3Len(&rhs));

            // clamp

            if (angle > 1.0f) {
                angle = 1.0f;
            }

            if (angle < -1.0f) {
                angle = -1.0f;
            }

            return acos(angle);
        }

        inline bool IsInvalid() const {
            if (
                FloatAbs(x) < NW4R_MATH_FLT_EPSILON &&
                FloatAbs(y) < NW4R_MATH_FLT_EPSILON &&
                FloatAbs(z) < NW4R_MATH_FLT_EPSILON
            ) {
                return true;
            }

            return false;
        }
        
        inline float Length() const {
            return PSVECMag(*this);
        }

        inline void Normalize() {
            VEC3Normalize(this, this);
        }

        inline void Normalize(const Vec3& other) {
            VEC3Normalize(this, &other);
        }

        static inline float Dot1(const Vec3& a, const Vec3& b);
        static inline float Dot2(const Vec3& a, const Vec3& b);
        static inline Vec3 Cross(const Vec3& a, const Vec3& b);
        static inline void Normalize(Vec3& out, const Vec3& in);
    };

    // these need to be outside to match

    // inline Vec3 Vec3::operator+(const Base& rhs) const {
    //     Vec3 v(0);
    //     VEC3Add(&v, this, &rhs);
    //     return v;
    // }

    inline Vec3 Vec3::operator+(const Vec3& rhs) const {
        Vec3 v(0);
        VEC3Add(&v, this, &rhs);
        return v;
    }
    
    // inline Vec3 Vec3::operator-(const Base& rhs) const {
    //     Vec3 v(0);
    //     const Base* r = &rhs;
    //     VEC3Sub(&v, this, &rhs);
    //     return v;
    // }

    inline Vec3 Vec3::operator-(const Vec3& rhs) const {
        Vec3 v(0);
        const Base* r = &rhs;
        VEC3Sub(&v, this, r);
        return v;
    }

    inline Vec3 Vec3::operator*(float scalar) const {
        Vec3 v(0);
        VEC3Scale(&v, this, scalar);
        return v;
    }

    inline Vec3 Vec3::Cross(const Vec3& a, const Vec3& b) {
        Vec3 v(0);
        PSVECCrossProduct(a, b, v);
        return v;
    }

    inline float Vec3::Dot1(const Vec3& a, const Vec3& b) {
        // i guess they wrote the assembly themselves?
        const Vec3* l = &a;
        const Vec3* r = &b;
        return DotProduct1(l, r);
    }

    inline float Vec3::Dot2(const Vec3& a, const Vec3& b) {
        const Vec3* l = &a;
        const Vec3* r = &b;
        return DotProduct2(l, r);
    }

    inline void Vec3::Normalize(Vec3& out, const Vec3& in) {
        Vec* a = (Vec*)&out;
        Vec* b = (Vec*)&in;
        PSVECNormalize(a, b);
    }
}
#endif
