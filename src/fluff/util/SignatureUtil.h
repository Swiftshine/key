#ifndef FLUFF_SIGNATUREUTIL_H
#define FLUFF_SIGNATUREUTIL_H

#include "types.h"
#include <string>

namespace SignatureUtil {
    uint GetSignature(const std::string& str);
    std::string GetSignature(uint src);
    void GetSignature(uint src, char* dst1, char* dst2, char* dst3, char* dst4);
}

// listed are the different signature types seen in structures related to game work
// A___ = Area [number]
// E___ = Environment [number]
// SN__ = Stage (Normal) [number]
// SB__ = Stage (Boss) [number]
// C___ = ?

#endif
