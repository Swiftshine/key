#include <game/util/MissionUtil.h>
#include <game/util/Literals.h>

using namespace FluffUtil;

int Mission::GetMissionTypeByCode(int code) {
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

int Mission::GetMissionCodeByType(int type) {
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

int Mission::GetMissionCountByType(int type) {
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

int Mission::GetMissionIDBaseByType(int type) {
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

char Mission::GetMissionIdentifierByType(int type) {
    char ret = 0;
    int t = static_cast<signed long>(type);

    if (type >= 0 && t<6) {
        ret = MissionIndicators[type];
        
    }

    return ret;
}

bool Mission::HasMissionIndicator(int type, gfl::BasicString* str) {
    bool ret = false;
    u32 len;
    char target;
    int charIndex;
    if (type > -1) {
        if (GFL_BASIC_STRING_CHECK_USE_STRING(str)) {
            len = str->length;
        } else {
            len = str->shortLen;
        }

        if (len) {
            target = GetMissionIdentifierByType(type);
            charIndex = str->FindChar(target, 0);

            if (charIndex != -1) {
                ret = true;
            }
        }

    }

    return ret;
}
