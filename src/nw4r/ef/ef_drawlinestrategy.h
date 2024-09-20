#ifndef NW4R_EF_DRAW_LINE_STRATEGY_H
#define NW4R_EF_DRAW_LINE_STRATEGY_H
#include "nw4r/types_nw4r.h"
#include "ef_drawstrategyimpl.h"

namespace nw4r
{
    namespace ef
    {
        class DrawLineStrategy : public DrawStrategyImpl
        {
        public:
            DrawLineStrategy();
            virtual ~DrawLineStrategy() {} // at 0x8
            
            virtual UNKTYPE Draw(const DrawInfo &, ParticleManager *);
        };
    }
}

#endif
