#include "util/SignatureUtil.h"

// last remaining nonmatching function in this TU
// https://decomp.me/scratch/yfkZ1
uint SignatureUtil::GetSignature(const std::string& str) {
    u32 len = str.length();

    if (len == 0) {
        return 'NONE';
    }
    
    if (len < 4) {
        return 'NONE';
    }

    uint signature = 0;

    // signature = (c & 0xFF) | (c << 8 & 0xFF00) | (c << 16 & 0xFF0000) | (c << 24 & 0xFF000000);
    signature += str[3] << 0 & 0xFF;
    signature += str[2] << 8 & 0xFF00;
    signature += str[1] << 16 & 0xFF0000;
    signature += str[0] << 24 & 0xFF000000;

    if (signature == 0) {
        signature = 'NONE';
    }

    return signature;
}


char empty[] = { 0 };

std::string SignatureUtil::GetSignature(uint src) {
    std::string result = empty;
    result += src >> 0x18 & 0xFF;
    result += src >> 0x10 & 0xFF;
    result += src >> 0x8 & 0xFF;
    result += src & 0xFF;
    return result;
}

void SignatureUtil::GetSignature(uint src, char* dst1, char* dst2, char* dst3, char* dst4) {
    *dst1 = src >> 0x18 & 0xFF;
    *dst2 = src >> 0x10 & 0xFF;
    *dst3 = src >> 0x8 & 0xFF;
    *dst4 = src & 0xFF;
}