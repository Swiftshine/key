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
        bool m_4;
        bool m_5;
        bool m_6;
        u32 m_8;
        u32 m_C;
        u32 m_10;
        u32 m_14;
        u32 m_18;
        u32 m_1C;
        nw4r::g3d::ScnRoot* mpScnRoot;
        u32 m_24;
        u32 m_28;
        u32 m_2C;
    };
}

#endif
