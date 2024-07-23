#ifndef GFL_PARAM_BASE_H
#define GFL_PARAM_BASE_H

#include <flf_types.h>
#include <gfl/string/basicstring.h>
#include <gfl/string.h>
namespace gfl {
    
// struct Param {
//     char label[32];
//     u32 hash;       // calcluated with Good-Feel's hash calculation
//     union {
//         char* string_val;
//         u32 uint_val;
//         s32 sint_val;
//         f32 float_val;
//         bool bool_val;
//     } value;
//     char* parameter_type;
// };


class Param {
public:
    Param(const char* newLabel);

    virtual void vf8() = 0;
    virtual void vfC() = 0;
    virtual ~Param();
    virtual void vf14() = 0;
public:
    char label[32];
    u32  hash;
};
} // namespace gfl

#endif
