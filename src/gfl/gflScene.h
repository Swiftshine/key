#ifndef GFL_SCENE_H
#define GFL_SCENE_H

#include "types.h"
#include "gflLinkedList.h"
#include <nw4r/g3d.h>

namespace gfl {
class RenderObj;

class Scene {
    public:
        Scene(u8 heapID, uint arg2, uint arg3);

        void Destroy(gfl::RenderObj* renderObj);
        void fn_80649178(gfl::RenderObj* renderObj);
        void AddRenderObj(gfl::RenderObj* renderObj);
        
        virtual ~Scene();
        virtual bool AreListsEmpty();
        virtual void Insert(nw4r::g3d::ScnObj* object);
        virtual void Remove(u32 index);
        virtual void DrawOpa();
        virtual void DraXlu();
        virtual bool IsScnRootSizeValid();
    protected:
        bool m_4;
        bool m_5;
        bool mIsUpdated;
        gfl::LinkedList<RenderObj> mRenderObjList;
        gfl::LinkedList<placeholder_t> m_14;
        nw4r::g3d::ScnRoot* mScnRoot;
        uint m_24;
        uint m_28;
        uint m_2C;
    };
}


#endif
