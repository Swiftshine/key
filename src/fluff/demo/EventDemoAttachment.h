#ifndef FLUFF_EVENTDEMOATTACHMENT_H
#define FLUFF_EVENTDEMOATTACHMENT_H

#include "types.h"
#include <string>

namespace demo {
    class EventDemoAttachment {
    public:

        /* Constructor */

        EventDemoAttachment();

        /* Virtual Methods */

        /* 0x08 */ virtual ~EventDemoAttachment();
        /* 0x0C */ virtual void vfC();
        /* 0x10 */ virtual void vf10();
        /* 0x14 */ virtual void vf14();
        /* 0x18 */ virtual void vf18();
        /* 0x1C */ virtual void vf1C();

        /* Class Members */

        /* 0x04 */ std::string m_4;
        /* 0x10 */ void* m_10;
    };

    // ASSERT_SIZE(EventDemoAttachment, 0x14);
}

#endif
