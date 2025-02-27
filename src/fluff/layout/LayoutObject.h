#ifndef FLUFF_LAYOUTOBJECT_H
#define FLUFF_LAYOUTOBJECT_H

#include "types.h"
#include <string>
#include <nw4r/lyt/lyt_drawInfo.h>
#include "gfl/gflTask.h"
#include "message/MessageTagProcessor.h"
#include "layout/LayoutObjectRender.h"

namespace layout {
    // size: 0x138
    class LayoutObject {
    public:
        LayoutObject(gfl::Task* parentTask, const char* layoutName);
        virtual ~LayoutObject();

    private:
        gfl::Task mTask1; // @ 0x4, size: 0x18
        gfl::Task mTask2; // @ 0x1C,
        int m_34;
        int m_38;
        nw4r::lyt::DrawInfo mDrawInfo; //  @ 0x3C, size: 0x54
        int m_90;
        message::MessageTagProcessor mMessageTagProcessor; // @ 0x94, size: 0xC
        std::string mArchivePath; // @ 0xA0, size: 0xC
        std::string mBRLYTPath; // @ 0xAC
        int m_B8;
        int m_BC;
        int m_C0;
        int m_C4;
        layout::LayoutObjectRender* mObjectRender; // @ 0xC8
        bool m_CC;
        bool m_CD;
        int m_D0;
        int m_D4;
        int m_D8;
        int* m_DC;
        int m_E0;
        int m_E4;
        int m_E8;
        int* m_EC;
        int* m_F0[4];
        u8 m_100[16];
        u8 m_110[32];
        int m_130;
        int m_134;
    };
}

#endif