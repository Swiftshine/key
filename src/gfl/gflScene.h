#ifndef GFL_SCENE_H
#define GFL_SCENE_H

#include "types.h"
#include "gflLinkedList.h"
#include <nw4r/g3d/g3d_scnroot.h>

namespace gfl {
class RenderObj;

class Scene {
    public:
        Scene(u8 heapID, uint maxNumChildren, uint maxNumScnObj);

        // either add to the list or remove it
        void HandleRenderObj(gfl::RenderObj* renderObj);
        void AddRenderObj(gfl::RenderObj* renderObj);
        void RemoveRenderObj(gfl::RenderObj* renderObj);
        
        virtual ~Scene();
        virtual bool AreListsEmpty();
        virtual void Insert(nw4r::g3d::ScnObj* object);
        virtual void Remove(nw4r::g3d::ScnObj* object);
        virtual void DrawOpa();
        virtual void DrawXlu();
        virtual bool IsScnRootSizeValid();

        inline nw4r::g3d::ScnRoot* GetScnRoot() {
            return mScnRoot;
        }

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
