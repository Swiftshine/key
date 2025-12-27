#ifndef FLUFF_MESSAGETAGPROCESSOR_H
#define FLUFF_MESSAGETAGPROCESSOR_H

#include "types.h"
#include <nw4r/ut/ut_TagProcessorBase.h>

namespace message {

/// @note Size: `0xC`
class MessageTagProcessor : public nw4r::ut::TagProcessorBase<wchar_t> {
public:
    

    MessageTagProcessor();

    /* Virtual Methods */
    
    /* 0x08 */ virtual ~MessageTagProcessor();
    /* 0x0C */ virtual Operation Process(u16 ch, ContextType* pCtx) override;
    /* 0x10 */ virtual Operation CalcRect(Rect* pRect, u16 ch, ContextType* pCtx) override;

    /* Class Members */

    /* 0x4 */ float m_4;
    /* 0x8 */ u8 m_8;
    /* 0x9 */ u8 m_9;
    /* 0xA */ u8 m_A;
    /* 0xB */ u8 m_B;
};

}

#endif