#ifndef GFL_PARAM_BASE_H
#define GFL_PARAM_BASE_H

#include <gfl/gfl_types.h>
#include <gfl/string/BasicString.h>
#include <gfl/string.h>
#include <gfl/console/Console.h>

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

    virtual int vf8() = 0;
    virtual void vfC() = 0;
    virtual ~Param();
    virtual void Print(gfl::Console* console, u32 count) = 0;

    bool Matches(const char* compLabel, u32 compHash);
    void PrintRepeat(gfl::Console* console, u32 count);
public:
    char label[32];
    u32  hash;
};
} // namespace gfl

#endif
