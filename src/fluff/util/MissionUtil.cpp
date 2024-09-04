#include "util/MissionUtil.h"
#include "util/SignatureUtil.h"
#include <cstdio>

static const char MissionIndicators[] = "NBTDCS";
static const char* MissionNameTemplate = "M%c%02d";
int MissionUtil::GetMissionTypeByCode(int code) {
    int ret = MissionType::None;
    int curType;
    int c;

    for (curType = MissionType::Bead; curType < 6; curType++) {
        c = GetMissionCodeByType(curType);
        if (code == c) {
            ret = curType;
            break;
        }
    }

    return ret;
}

int MissionUtil::GetMissionCodeByType(int type) {
    int ret = MissionCode::None;
    switch (type) {
        case MissionType::Bead:   ret = MissionCode::Bead; break;
        case MissionType::Time:   ret = MissionCode::Time; break;
        case MissionType::Defeat: ret = MissionCode::Defeat; break;
        case MissionType::Carry:  ret = MissionCode::Carry; break;
        case MissionType::Seek:   ret = MissionCode::Seek; break;
    }
    return ret;
}

int MissionUtil::GetMissionCountByType(int type) {
    int ret = MissionCount::None;
    switch (type) {
        case MissionType::Bead:   ret = MissionCount::Bead; break;
        case MissionType::Time:   ret = MissionCount::Time; break;
        case MissionType::Defeat: ret = MissionCount::Defeat; break;
        case MissionType::Carry:  ret = MissionCount::Carry; break;
        case MissionType::Seek:   ret = MissionCount::Seek; break;
    }
    return ret;
}

int MissionUtil::GetMissionIDBaseByType(int type) {
    int ret = MissionIDBase::None;
    switch (type) {
        case MissionType::Bead:   ret = MissionIDBase::Bead; break;
        case MissionType::Time:   ret = MissionIDBase::Time; break;
        case MissionType::Defeat: ret = MissionIDBase::Defeat; break;
        case MissionType::Carry:  ret = MissionIDBase::Carry; break;
        case MissionType::Seek:   ret = MissionIDBase::Seek; break;
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
        if (0 != str.size() /* && str.find(GetMissionIdentifierByType(type)) != std::string::npos */) {
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
        type = MissionType::None;
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

extern "C" int snprintf(char*, size_t, const char*, ...);

uint MissionUtil::GetMissionMagicByID(int id) {
    int type;
    int index;
    GetMissionInfoByID(id, &type, &index);
    
    if (MissionType::None != type) {
        char types[] = {'\0', 'B', 'T', 'D', 'C', 'S'};
        char magicStr[16];
        snprintf(magicStr, sizeof(magicStr), "M%c%02d", types[type], index);
        magicStr[4] = 0;
        
        return SignatureUtil::GetSignature(std::string(std::string(magicStr)));
    }
    return 'NONE';
}