#include <gfl/string.h>
#include <gfl/mem/Mem.h>

u32 gfl::ToHash(const char* src) {
    if (!src) return 0;
    
    u32  result = 0;

    while (*src) {
        result = *src + result * 0x89;
        src++;
    }

    return result;
}
