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
        /* 0x14 */ virtual int vf14_(); // *
        /* 0x18 */ virtual void vf18();
        /* 0x1C */ virtual void vf1C();

        /* Class Members */

        /* 0x04 */ std::string m_4;
        /* 0x10 */ void* m_10;
    };

    /* *Temporary rename with underscore until the name of either it or
        FlfGameObj::vf14 is found.
    */

    // ASSERT_SIZE(EventDemoAttachment, 0x14);
}

#endif
