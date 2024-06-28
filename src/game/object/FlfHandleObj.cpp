#include <game/object/FlfHandleObj.h>

FlfHandleObj::FlfHandleObj() {
    this->task = NULL;
    this->_8   = NULL;
    fn_801688b4(lbl_808E4FF8, this);
}

FlfHandleObj::~FlfHandleObj() {
    fn_80168924(lbl_808E4FF8, this);
}