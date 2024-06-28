#include <gfl/string.h>
#include <gfl/mem.h>

u32 gfl::String::ToHash(const char* src) {
    if (!src) return 0;
    
    char curChar;
    u32 result = 0;

    while (true) {
        curChar = *src;
        if (!curChar) break;
        src++;
        result = curChar + result * 0x89;
    }
    return result;
}
