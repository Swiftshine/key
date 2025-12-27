#ifndef GFL_SCNMDLEXPANDWRAPPER_H
#define GFL_SCNMDLEXPANDWRAPPER_H

#include <nw4r/g3d/g3d_scnmdlexpand.h>

namespace gfl {

/// @note Size: `0xC`
class ScnMdlExpandWrapper {
public:
    inline ScnMdlExpandWrapper() {
        // blah
    }

    /* 0x8 */ virtual ~ScnMdlExpandWrapper();

    /* Class Members */

    /* 0x4 */ bool mIsVisible;
    /* 0x8 */ nw4r::g3d::ScnMdlExpand* mScnMdlExpand;
};
}

#endif