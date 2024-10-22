#ifndef FLUFF_COLDATASEG_H
#define FLUFF_COLDATASEG_H


#include "types.h"

#include "object/collision/ColData.h"
#include <utility>
#include "util/KdTreeUtil.h"

class ColDataSeg : public ColData {
public:
    ColDataSeg();
    DECL_WEAK virtual ~ColDataSeg();

    void AddSelf();
    void RemoveSelf();
private:
    u16 mIndex;
    u16 m_22;
    std::pair<nw4r::math::VEC2, nw4r::math::VEC2> mPoints;
    nw4r::math::VEC2 m_34;
    uint m_3C;
};

#endif
