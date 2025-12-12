#include "graphics/FbMem.h"
#include "GX/GXTexture.h"
#include "GX/GXTypes.h"
#include <revolution/GX.h>

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480


// nonmatching because of gfl::Task
void FbMem::Setup() {
    size_t size = GXGetTexBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT, GX_TF_RGBA8, FALSE, 0);

    Buf1 = FrameBuffer(size);
    Buf2 = FrameBuffer(size);

    size = GXGetTexBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT, GX_TF_RGB565, FALSE, 0);
    Buf3 = FrameBuffer(size);

    // need to fix this later
    // sClearFlagTask = new (gfl::HeapID::Work) gfl::Task(ClearFlag, "FbMem::ClearFlag");
    sClearFlagTask->SetFlags(0x78);
    Stage::sDrawRootTask->MakeChild(sClearFlagTask);
}

void FbMem::Shutdown() {
    delete sClearFlagTask;
    sClearFlagTask = nullptr;

    FrameBuffer* buf = &Buf1;

    for (uint i = 0; i < 3; i++, buf++) {
        gfl::Free(buf->mData);
        buf->mData = nullptr;
    }
}

void* FbMem::GetFrameBufferData(int id, size_t size, bool refresh) {
    FrameBuffer* buf = GetFrameBuffer(id);
    
    void* ret;

    if (buf == nullptr) {
        ret = nullptr;
    } else {
        buf->mID = id;
        buf->mDoRefresh = refresh;
        ret = buf->mData;
    }

    return ret;
}

void FbMem::DisableFrameBuffer(int id) {
    FrameBuffer* buf = &Buf1;

    for (uint i = 0; i < 3; i++, buf++) {
        if (buf->m_0 == lbl_80840F38[id] && buf->mID == id) {
            buf->mID = -1;
            buf->mDoRefresh = false;
            return;
        }
    }
}

void FbMem::ClearFlag() {
    FrameBuffer* buf = &Buf1;

    for (uint i = 0; i < 3; i++, buf++) {
        if (!buf->mDoRefresh) {
            buf->mID = -1;
        }
    }
}

FbMem::FrameBuffer* FbMem::GetFrameBuffer(int id) {
    int unk = lbl_80840F38[id];

    FrameBuffer* buf = &Buf1;

    for (uint i = 0; i < 3; i++, buf++) {
        if (buf->m_0 == unk && (buf->mID == -1 || buf->mID == id)) {
            return buf;
        }
    }

    return nullptr;
}
