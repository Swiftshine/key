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
    
    LayoutObject(gfl::Task* pParentTask, const char* pLayoutName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~LayoutObject();

    /* Class Members */

    /* 0x004 */ gfl::Task mTask1;
    /* 0x01C */ gfl::Task mTask2;
    /* 0x034 */ s32 m_34;
    /* 0x038 */ s32 m_38;
    /* 0x03C */ nw4r::lyt::DrawInfo mDrawInfo;
    /* 0x090 */ s32 m_90;
    /* 0x094 */ message::MessageTagProcessor mMessageTagProcessor;
    /* 0x0A0 */ std::string mArchivePath;
    /* 0x0AC */ std::string mBRLYTPath;
    /* 0x0B8 */ s32 m_B8;
    /* 0x0BC */ s32 m_BC;
    /* 0x0C0 */ s32 m_C0;
    /* 0x0C4 */ s32 m_C4;
    /* 0x0C8 */ layout::LayoutObjectRender* mObjectRender;
    /* 0x0CC */ bool m_CC;
    /* 0x0CD */ bool m_CD;
    /* 0x0D0 */ s32 m_D0;
    /* 0x0D0 */ s32 m_D4;
    /* 0x0D8 */ s32 m_D8;
    /* 0x0DC */ s32* m_DC;
    /* 0x0E0 */ s32 m_E0;
    /* 0x0E4 */ s32 m_E4;
    /* 0x0E8 */ s32 m_E8;
    /* 0x0EC */ s32* m_EC;
    /* 0x0F0 */ s32* m_F0[4];
    /* 0x100 */ u8 m_100[16];
    /* 0x110 */ u8 m_110[32];
    /* 0x130 */ s32 m_130;
    /* 0x134 */ s32 m_134;
};

}

#endif
