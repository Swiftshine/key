#ifndef GFL_SCENE_H
#define GFL_SCENE_H

#include <nw4r/g3d/g3d_scnroot.h>

namespace gfl {

    // size unk
    class Scene {
    public:
        Scene(u8 heapID, u32 arg2, u32 arg3);

        virtual ~Scene();
        virtual void vfC();
        virtual void vf10();
        virtual void vf14();
        virtual void vf18();
        virtual void vf1C();
        virtual void vf20();
    public:
        bool _4;
        bool _5;
        bool _6;
        u8 pad;
        u32 _8;
        u32 _C;
        u32 _10;
        u32 _14;
        u32 _18;
        u32 _1C;
        nw4r::g3d::ScnRoot* scnRoot;
        u32 _24;
        u32 _28;
        u32 _2C;
    };
}

#endif
