#ifndef FLUFF_FBMEM_H
#define FLUFF_FBMEM_H

#include "types.h"
#include "game/Game.h"
#include "gfl/gflTask.h"
#include "manager/Stage.h"

// Frame Buffer Memory
namespace FbMem {
    /// @note Size: `0x14`
    struct FrameBuffer {
        FrameBuffer() { }

        FrameBuffer(size_t size)
            : m_0(0)
            , mID(-1)
            , mData(gfl::Alloc(Game::Mem2Heap, size, 0x20))
            , mDoRefresh(false)
        { }
        
        /* 0x00 */ int m_0;
        /* 0x04 */ int mID;
        /* 0x08 */ void* mData;
        /* 0x0C */ size_t mSize;
        /* 0x10 */ bool mDoRefresh;
    };

    FrameBuffer Buf1;   // RGBA8
    FrameBuffer Buf2; 
    FrameBuffer Buf3;   // RGB565

    static gfl::Task* sClearFlagTask;

    int lbl_80840F38[10 /* ? */]; // .data

    void Setup();
    void Shutdown();
    void* GetFrameBufferData(int id, size_t size, bool refresh);
    void DisableFrameBuffer(int id);
    void ClearFlag();
    FrameBuffer* GetFrameBuffer(int id);
}

#endif
