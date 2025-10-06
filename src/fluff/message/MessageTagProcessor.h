#ifndef FLUFF_MESSAGETAGPROCESSOR_H
#define FLUFF_MESSAGETAGPROCESSOR_H

#include "types.h"

namespace message {

/// @note Size: `0xC`
class MessageTagProcessor {
public:
    /* Constructor */

    MessageTagProcessor();

    /* Virtual Methods */
    
    /* 0x08 */ virtual ~MessageTagProcessor();

    /* Class Members */

    /* 0x4 */ float m_4;
    /* 0x8 */ u8 m_8;
    /* 0x9 */ u8 m_9;
    /* 0xA */ u8 m_A;
    /* 0xB */ u8 m_B;
};

ASSERT_SIZE(MessageTagProcessor, 0xC);

}

#endif