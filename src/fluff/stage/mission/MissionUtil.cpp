#include "stage/mission/MissionUtil.h"
#include "util/SignatureUtil.h"
#include <cstdio>

static const char MissionIndicators[] = "NBTDCS";
static const char* MissionNameTemplate = "M%c%02d";
s32 MissionUtil::GetMissionTypeByCode(s32 code) {
    s32 ret = MissionUtil::eMissionType_None;
    s32 curType;
    s32 c;

    for (curType = MissionUtil::eMissionType_Bead; curType < 6; curType++) {
        c = GetMissionCodeByType(curType);
        if (code == c) {
            ret = curType;
            break;
        }
    }

    return ret;
}

s32 MissionUtil::GetMissionCodeByType(s32 type) {
    s32 ret = MissionUtil::eMissionCode_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionCode_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionCode_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionCode_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionCode_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionCode_Seek; break;
    }
    return ret;
}

s32 MissionUtil::GetMissionCountByType(s32 type) {
    s32 ret = MissionUtil::eMissionCount_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionCount_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionCount_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionCount_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionCount_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionCount_Seek; break;
    }
    return ret;
}

s32 MissionUtil::GetMissionIDBaseByType(s32 type) {
    s32 ret = MissionUtil::eMissionIDBase_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionIDBase_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionIDBase_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionIDBase_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionIDBase_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionIDBase_Seek; break;
    }
    return ret;
}

char MissionUtil::GetMissionIdentifierByType(s32 type) {
    char ret = 0;
    s32 t = static_cast<signed long>(type);

    if (type >= 0 && t<6) {
        ret = MissionIndicators[type];

    }

    return ret;
}

bool MissionUtil::HasMissionIndicator(s32 type, const std::string& str) {
    bool ret = false;
    u32 len;
    char target;
    s32 charIndex;
    signed long t = static_cast<signed long>(type);

    if (type >= 0 && t < 6) {
        if (0 != str.length() && std::string::npos != str.rfind(GetMissionIdentifierByType(type), 0)) {
            ret = true;
        }
    }

    return ret;
}

s32 MissionUtil::GetMissionIDByInfo(s32 type, s32 index) {
    s32 id = GetMissionIDBaseByType(type);
    s32 count = GetMissionCountByType(type);

    if (index < 0 || count <= index) {
        id = 0;
    } else {
        id += index;
    }

    return id;
}


void MissionUtil::GetMissionInfoByID(s32 id, s32* destType, s32* destIndex) {
    signed long t;
    s32 type;
    s32 index;
    bool isValid = false;

    isValid = false;
    type  = id / 100;
    index = id % 100;
    t = static_cast<signed long>(type);

    if (type >= 1 && t < 6) {
        s32 count  = GetMissionCountByType(type);

        if (index >= 0 && index < count) {
            isValid = true;
        }
    }

    if (!isValid) {
        type = MissionUtil::eMissionType_None;
        index = 0;
    }

    if (destType) {
        *destType = type;
    }

    if (destIndex) {
        *destIndex = index;
    }
}

s32 MissionUtil::GetMissionTypeByID(s32 id) {
    s32 type;
    GetMissionInfoByID(id, &type, nullptr);
    return type;
}

s32 MissionUtil::GetMissionIndexByID(s32 id) {
    s32 index;
    GetMissionInfoByID(id, nullptr, &index);
    return index;
}

const char magic_template[] = "M%c%02d";
u32 MissionUtil::GetMissionMagicByID(s32 id) {
    s32 type;
    s32 index;
    GetMissionInfoByID(id, &type, &index);

    if (MissionUtil::eMissionType_None != type) {
        char types[] = {'\0', 'B', 'T', 'D', 'C', 'S'};
        char magicStr[16];
        snprintf(magicStr, sizeof(magicStr), magic_template, types[type], index);
        magicStr[4] = 0;

        return SignatureUtil::GetSignature(std::string(std::string(magicStr)));
    }
    return 'NONE';
}
