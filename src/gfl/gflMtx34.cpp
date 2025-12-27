#include <cmath>
#include "gflMtx34.h"

// probably all inline methods that just got emitted from
// gfl::ScnMdlWrapper's tu

using namespace gfl;

inline bool Finite(float f) {
    return isfinite(f);
}

inline bool Nan(float f) {
    return isnan(f);
}

bool Mtx34::IsValid() {
    for (uint i = 0; i < 12; i++) {
        if (!Finite(a[i]) || Nan(a[i])) {
            return false;
        }
    }

    return true;
}