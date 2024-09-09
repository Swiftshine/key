#include "util/GimmickUtil.h"
#include "object/FlfMdlDraw.h"

int GimmickUtil::GetGimmickIDByDescription(const char* description) {
    GimmickEntry* entry = GimmickTable;
    uint id = 0;

    while (id < GimmickIDs::GimmickTypeCount + 1) {
        if (nullptr != entry->GetDescription() && 0 == strcmp(entry->GetDescription(), description)) {
            return id;
        }
        id++;
        entry++;
    }

    return -1;
}

const char* GimmickUtil::GetResourceNameByGimmickID(int id) {
    return GimmickTable[id].GetResourceName();
}

std::string GimmickUtil::GetResourcePathByGimmickID(int id) {
    std::string str = "gimmick/";
    str += GetResourceNameByGimmickID(id);
    return str;
}

GimmickBuildFunction GimmickUtil::GetBuildFunctionByGimmickID(int id) {
    return GimmickTable[id].GetBuildFunction();
}

bool GimmickUtil::CheckCommonByGimmickID(int id) {
    return GimmickTable[id].IsCommon();
}

bool GimmickUtil::IsBead(int id) {
    return 21 <= id && id <= 42;
}

int GimmickUtil::fn_80050700(int id) {
    switch (id) {
        case 0x15:
        case 0x1C:
        case 0x23:
        case 0x2A: return 0;

        case 0x16:
        case 0x1D:
        case 0x24: return 1;

        case 0x17:
        case 0x1E:
        case 0x25: return 2;

        case 0x18:
        case 0x1F:
        case 0x26: return 3;

        case 0x19:
        case 0x20:
        case 0x27: return 4;

        case 0x1A:
        case 0x21:
        case 0x28: return 5;

        case 0x1B:
        case 0x22:
        case 0x29: return 6;

        default: return 7;
    }
}

int GimmickUtil::fn_80050764(int arg0, int arg1) {
    if (arg0 >= 4) {
        return 0x15;
    }

    if (arg1 >= 7) {
        return 0x15;
    }

    if (3 == arg0) {
        return 0x2A;
    }

    int temp = arg0 * 7 + 0x15;
    temp += arg1;
    return temp;
}

bool GimmickUtil::fn_800507A8(int id) {
    return 0x43 <= id && id <= 0x46;
}

bool GimmickUtil::fn_800507C8(int id) {
    return 0x130 <= id && id <= 0x138;
}

void GimmickUtil::GetButtonBRRES(gfl::ResInfo** dest) {
    FlfMdlDraw::GetFileInfoFromArchive(dest, "gimmick/button/button.brres");
}