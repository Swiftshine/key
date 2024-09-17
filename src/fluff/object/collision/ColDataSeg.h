#ifndef FLUFF_COLDATASEG_H
#define FLUFF_COLDATASEG_H


#include "types.h"
#include "gfl/gflVec2.h"
#include "object/collision/ColData.h"
#include <utility>
#include "util/KdTreeUtil.h"

class ColDataSeg : public ColData {
public:
    ColDataSeg();

    virtual int GetNodePlacement(KdTreeSplitInfo&);
    virtual bool ArePointsInRect(gfl::Vec2*);
    DECL_WEAK virtual ~ColDataSeg();

    void AddSelf();
    void RemoveSelf();
private:
    u16 mIndex;
    u16 m_22;
    std::pair<gfl::Vec2, gfl::Vec2> mPoints;
    gfl::Vec2 m_34;
    uint m_3C;
};

#endif
