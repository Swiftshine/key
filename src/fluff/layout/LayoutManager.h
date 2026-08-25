#ifndef FLUFF_LAYOUT_LAYOUTMANAGER_H
#define FLUFF_LAYOUT_LAYOUTMANAGER_H

#include <types.h>

#include <gfl/gflTask.h>
#include <gfl/gflVec2.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include "layout/LayoutResource.h"

namespace layout {

static u8 AllocatingHeapID = gfl::eHeapID_Work;
static u8 HeapID = gfl::eHeapID_Work;

/// @note Size: `0x88`
class LayoutManager {
    struct Substruct {
        Substruct() {
            for (u32 i = 0; i < 4; i++) {
                m_0[i][0] = 0.0f;
                m_0[i][1] = 0.0f;
            }
        }
        
        f32 m_0[4][2];
    };
public:
    static LayoutManager* CreateInstance(gfl::Task* pParentTask, u8 taskFlags, u8 allocatingHeapID, u8 heapID);
    static void DestroyInstance();
    static LayoutManager* GetInstance();
    
    LayoutManager(gfl::Task* pParentTask, u8 taskFlags);
    
    /* 0x8 */ virtual ~LayoutManager();
    /* 0xC */ virtual void Update();
    
    void Init();
    void fn_8003867C(u8 index, f32 x, f32 y);
    void fn_800386A8(u8 index, const gfl::Vec2&);
    s32 LoadResource(const char* pResourceName);
    s32 fn_800387CC(const char*);
    s32 RemoveResource(const char* pResourceName);
    
    static void Cleanup();
    static void fn_80038700(gfl::Vec2&, const gfl::Vec2&);
    static void* fn_8003880C();
    static void fn_80038828(u32, u32);

private:
    /* 0x04 */ gfl::Task mTask;
    /* 0x1C */ nw4r::ut::Rect mRect1;
    /* 0x2C */ nw4r::ut::Rect mRect2;
    /* 0x3C */ Substruct m_3C;
    /* 0x5C */ LayoutResource mLayoutResource;
};

}

#endif
