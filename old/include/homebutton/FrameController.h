#ifndef FLUFF_HOMEBUTTON_FRAME_CONTROLLER_H
#define FLUFF_HOMEBUTTON_FRAME_CONTROLLER_H

namespace homebutton {
    class FrameController {
    protected:
        FrameController();
    public:
        virtual ~FrameController() = 0;
        virtual void fn_806FF870() = 0;
    };
}

#endif
