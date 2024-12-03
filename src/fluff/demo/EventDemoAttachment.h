#ifndef FLUFF_EVENTDEMOATTACHMENT_H
#define FLUFF_EVENTDEMOATTACHMENT_H

#include "types.h"

namespace demo {
    class EventDemoAttachment {
    public:
        EventDemoAttachment();
        virtual ~EventDemoAttachment();

        virtual void vfC();
        virtual void vf10();
        virtual void vf14();
        virtual void vf18();
        virtual void vf1C();
    private:
        void* m_4;
        void* m_8;
        void* m_C;
        void* m_10;
    };

    ASSERT_SIZE(EventDemoAttachment, 0x14);
}

#endif
