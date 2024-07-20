#ifndef GFL_SCENE_H
#define GFL_SCENE_H

// #include <nw4r/g3d/g3d_scnmdl.h>

namespace gfl {

    class Scene {
    public:
        Scene(u8 heapID, );

        virtual ~Scene();
        virtual void vfC();
        virtual void vf10();
        virtual void vf14();
        virtual void vf18();
        virtual void vf1C();
        virtual void vf20();
    };
}

#endif
