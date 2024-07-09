#ifndef FLUFF_HOMEBUTTON_GROUP_ANM_CONTROLLER_H
#define FLUFF_HOMEBUTTON_GROUP_ANM_CONTROLLER_H

// #include <homebutton/FrameController.h>
#include <types.h>

#pragma code_merging on
#pragma force_active off

namespace homebutton {
    class GroupAnmController {
    public:
        GroupAnmController();
        virtual ~GroupAnmController();
        virtual void fn_806FF870();
    public:
        u32 _4;
        u32 _8;
        u32 _C;
        u32 _10;
        u32 _14;
        u32 _18;
        u32 _1C;
        void* _20;
        void* _24;
    };

    // ?
    // ASSERT_SIZE(GroupAnmController, 0x28)
}

#endif
