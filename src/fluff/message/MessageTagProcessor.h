#ifndef FLUFF_MESSAGETAGPROCESSOR_H
#define FLUFF_MESSAGETAGPROCESSOR_H

#include "types.h"

namespace message {
    class MessageTagProcessor {
    public:
        MessageTagProcessor();
        virtual ~MessageTagProcessor();
    private:
        float m_4;
        u8 m_8;
        u8 m_9;
        u8 m_A;
        u8 m_B;
    };

    ASSERT_SIZE(MessageTagProcessor, 0xC);
}

#endif