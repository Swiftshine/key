#ifndef GFL_ERROR_H
#define GFL_ERROR_H

#include <cstdio>
#include <cstdlib>

namespace gfl {
namespace error {
    inline void AllocError() {
        fprintf(stderr, "Memory allocation failure");
        abort();
    }
}
}
#endif