#include "stage/mission/MissionUtil.h"
#include "util/SignatureUtil.h"
#include <cstdio>

static const char MissionIndicators[] = "NBTDCS";
static const char* MissionNameTemplate = "M%c%02d";
int MissionUtil::GetMissionTypeByCode(int code) {
    int ret = MissionUtil::eMissionType_None;
    int curType;
    int c;

    for (curType = MissionUtil::eMissionType_Bead; curType < 6; curType++) {
        c = GetMissionCodeByType(curType);
        if (code == c) {
            ret = curType;
            break;
        }
    }

    return ret;
}

int MissionUtil::GetMissionCodeByType(int type) {
    int ret = MissionUtil::eMissionCode_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionCode_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionCode_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionCode_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionCode_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionCode_Seek; break;
    }
    return ret;
}

int MissionUtil::GetMissionCountByType(int type) {
    int ret = MissionUtil::eMissionCount_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionCount_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionCount_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionCount_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionCount_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionCount_Seek; break;
    }
    return ret;
}

int MissionUtil::GetMissionIDBaseByType(int type) {
    int ret = MissionUtil::eMissionIDBase_None;
    switch (type) {
        case MissionUtil::eMissionType_Bead:   ret = MissionUtil::eMissionIDBase_Bead; break;
        case MissionUtil::eMissionType_Time:   ret = MissionUtil::eMissionIDBase_Time; break;
        case MissionUtil::eMissionType_Defeat: ret = MissionUtil::eMissionIDBase_Defeat; break;
        case MissionUtil::eMissionType_Carry:  ret = MissionUtil::eMissionIDBase_Carry; break;
        case MissionUtil::eMissionType_Seek:   ret = MissionUtil::eMissionIDBase_Seek; break;
    }
    return ret;
}

char MissionUtil::GetMissionIdentifierByType(int type) {
    char ret = 0;
    int t = static_cast<signed long>(type);

    if (type >= 0 && t<6) {
        ret = MissionIndicators[type];

    }

    return ret;
}

bool MissionUtil::HasMissionIndicator(int type, const std::string& str) {
    bool ret = false;
    uint len;
    char target;
    int charIndex;
    signed long t = static_cast<signed long>(type);

    if (type >= 0 && t < 6) {
        if (0 != str.length() && std::string::npos != str.rfind(GetMissionIdentifierByType(type), 0)) {
            ret = true;
        }
    }

    return ret;
}

int MissionUtil::GetMissionIDByInfo(int type, int index) {
    int id = GetMissionIDBaseByType(type);
    int count = GetMissionCountByType(type);

    if (index < 0 || count <= index) {
        id = 0;
    } else {
        id += index;
    }

    return id;
}


void MissionUtil::GetMissionInfoByID(int id, int* destType, int* destIndex) {
    signed long t;
    int type;
    int index;
    bool isValid = false;

    isValid = false;
    type  = id / 100;
    index = id % 100;
    t = static_cast<signed long>(type);

    if (type >= 1 && t < 6) {
        int count  = GetMissionCountByType(type);

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

int MissionUtil::GetMissionTypeByID(int id) {
    int type;
    GetMissionInfoByID(id, &type, nullptr);
    return type;
}

int MissionUtil::GetMissionIndexByID(int id) {
    int index;
    GetMissionInfoByID(id, nullptr, &index);
    return index;
}

const char magic_template[] = "M%c%02d";
uint MissionUtil::GetMissionMagicByID(int id) {
    int type;
    int index;
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
