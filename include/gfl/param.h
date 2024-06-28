#ifndef GFL_PARAM_H
#define GFL_PARAM_H

#include <types.h>

namespace gfl {
    
struct Param {
    char label[32];
    u32 hash;       // calcluated with Good-Feel's hash calculation
    union {
        char* string_val;
        u32 uint_val;
        s32 sint_val;
        f32 float_val;
        bool bool_val;
    } value;
    char* parameter_type;
};

} // namespace gfl

#endif