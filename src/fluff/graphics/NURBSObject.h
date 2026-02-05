#ifndef FLUFF_NURBSOBJECT_H
#define FLUFF_NURBSOBJECT_H

#include "graphics/MNEB.h"

class NURBS;
struct NURBSPointArray;

class NURBSObject {
public:
    /* Class Members */

    MNEB::CurveBlock* mCurveBlock;
    NURBS* mNURBS;
    NURBSPointArray* mPointArray;
    void* m_C;
};

#endif
