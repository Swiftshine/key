#ifndef GFL_VEC2_H
#define GFL_VEC2_H


namespace gfl {
    struct Vec2 {
        static const Vec2 Zero;

        Vec2() : x(0.0f), y(0.0f) {}
        float x, y;
        inline void operator=(float val) {
            x = val;
            y = val;
        }
    };
}

#endif
