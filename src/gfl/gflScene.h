#ifndef GFL_SCENE_H
#define GFL_SCENE_H

#include "types.h"

#include <list>
#include <nw4r/g3d/g3d_scnroot.h>
#include "gflTask.h"
#include "gflRenderObj.h"
#include "gflPointer.h"

namespace gfl {
class Scene {
    public:
        static bool XluSortCheck(nw4r::g3d::ScnLeaf* pA, nw4r::g3d::ScnLeaf* pB);
        static bool OpaSortCheck(nw4r::g3d::ScnLeaf* pA, nw4r::g3d::ScnLeaf* pB);
        static void InvalidateG3DState();
        
        Scene(u8 heapID, uint maxNumChildren, uint maxNumScnObj);

        virtual ~Scene();
        virtual bool AreListsEmpty() const;
        virtual void Insert(nw4r::g3d::ScnObj* object);
        virtual void Remove(nw4r::g3d::ScnObj* object);
        virtual void DrawOpa() const;
        virtual void DrawXlu() const;
        virtual bool IsScnRootSizeValid() const;

        void Init(const char* pSceneLabel, u8 gameTaskFlags, u8 worldMtxTaskFlags, u8 drawTaskFlags, Task* pParentGameTask, Task* pParentWorldMtxTask, Task* pParentDrawTask);
        void AddRenderObj(RenderObj* pRenderObj);
        void RemoveRenderObj(RenderObj* pRenderObj);
        void HandleRenderObj(RenderObj* pRenderObj);
        
        void GameUpdate() const;
        void WorldMtxUpdate() const;
        void DrawUpdate() const;

        void UpdateCamera();

        inline nw4r::g3d::ScnRoot* GetScnRoot() {
            return mScnRoot;
        }
    protected:
        /* 0x04 */ bool mShouldUpdate;
        /* 0x05 */ bool m_5; // debug related?
        /* 0x06 */ bool mIsWorldCalculated;
        /* 0x08 */ std::list<RenderObj*> mRenderObjs;
        /* 0x14 */ std::list<placeholder_t> m_14;
        /* 0x20 */ nw4r::g3d::ScnRoot* mScnRoot;
        /* 0x24 */ Pointer<Task> mGameTask;
        /* 0x28 */ Pointer<Task> mWorldMtxTask;
        /* 0x2C */ Pointer<Task> mDrawTask;
    };
}


#endif
