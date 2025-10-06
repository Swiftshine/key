#ifndef FLUFF_CBPLAYERBASE_H
#define FLUFF_CBPLAYERBASE_H

#include <nw4r/g3d/g3d_scnobj.h>

class CB_PlayerBase : public nw4r::g3d::IScnObjCallback {
public:

    /* Virtual Methods */
    
    /* 0x08 */ DECL_WEAK virtual ~CB_PlayerBase();
};

#endif
