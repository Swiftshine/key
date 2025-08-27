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
    /* Constructor */
    LayoutObject(gfl::Task* pParentTask, const char* pLayoutName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~LayoutObject();

    /* Class Members */

    /* 0x004 */ gfl::Task mTask1;
    /* 0x01C */ gfl::Task mTask2;
    /* 0x034 */ int m_34;
    /* 0x038 */ int m_38;
    /* 0x03C */ nw4r::lyt::DrawInfo mDrawInfo;
    /* 0x090 */ int m_90;
    /* 0x094 */ message::MessageTagProcessor mMessageTagProcessor;
    /* 0x0A0 */ std::string mArchivePath;
    /* 0x0AC */ std::string mBRLYTPath;
    /* 0x0B8 */ int m_B8;
    /* 0x0BC */ int m_BC;
    /* 0x0C0 */ int m_C0;
    /* 0x0C4 */ int m_C4;
    /* 0x0C8 */ layout::LayoutObjectRender* mObjectRender;
    /* 0x0CC */ bool m_CC;
    /* 0x0CD */ bool m_CD;
    /* 0x0D0 */ int m_D0;
    /* 0x0D0 */ int m_D4;
    /* 0x0D8 */ int m_D8;
    /* 0x0DC */ int* m_DC;
    /* 0x0E0 */ int m_E0;
    /* 0x0E4 */ int m_E4;
    /* 0x0E8 */ int m_E8;
    /* 0x0EC */ int* m_EC;
    /* 0x0F0 */ int* m_F0[4];
    /* 0x100 */ u8 m_100[16];
    /* 0x110 */ u8 m_110[32];
    /* 0x130 */ int m_130;
    /* 0x134 */ int m_134;
};

}

#endif