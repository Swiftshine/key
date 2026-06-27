#pragma pool_strings off

#include "manager/PlTransRes.h"
#include "manager/ResourceManager.h"
#include "gfl/gflAlloc.h"

void PlTransResMng::InitInstance() {
    sInstance = new (gfl::HeapID::Work) PlTransResMng;
}

void PlTransResMng::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

void PlTransResMng::AddPlayerResourceName(uint id) {
    const char* name = GetPlayerResourceName(id);
    ResourceManager::Instance()->AddCharaResourceName(name);
}

const char* PlTransResMng::GetPlayerResourceName(uint id) {
    switch (id) {
        case 0:  return "chara/new_player/FORM00/BODY";
        case 1:  return "chara/new_player/FORM00/FOOT";
        case 2:  return "chara/new_player/FORM00/MISSILE_02";
        case 3:  return "chara/new_player/FORM00/LIGHT";
        case 4:  return "chara/new_player/FORM00/1P_00_eye";
        case 5:  return "chara/new_player/FORM00/2P_00_eye";
        case 6:  return "chara/new_player/FORM00/1P_01_eye";
        case 7:  return "chara/new_player/FORM00/2P_01_eye";
        case 8:  return "chara/new_player/FORM00/ARM";
        case 9:  return "chara/new_player/FORM00/HAND";
        case 10: return "chara/new_player/FORM16/BODY";
        case 11: return "chara/new_player/FORM16/1P_00_eye";
        case 12: return "chara/new_player/FORM16/2P_00_eye";
        case 13: return "chara/new_player/FORM16/1P_01_eye";
        case 14: return "chara/new_player/FORM16/2P_01_eye";
        case 15: return "chara/new_player/FORM03/BODY";
        case 16: return "chara/new_player/FORM03/1P_00_eye";
        case 17: return "chara/new_player/FORM03/2P_00_eye";
        case 18: return "chara/new_player/FORM03/1P_01_eye";
        case 19: return "chara/new_player/FORM03/2P_01_eye";
        case 20: return "chara/new_player/FORM03/PARTS";
        case 21: return "chara/new_player/FORM03/ITEM";
        case 22: return "chara/new_player/FORM04/BODY";
        case 23: return "chara/new_player/FORM04/HOSE";
        case 24: return "chara/new_player/FORM04/WATER";
        case 25: return "chara/new_player/FORM04/1P_eye";
        case 26: return "chara/new_player/FORM04/2P_eye";
        case 27: return "chara/new_player/FORM05/BODY";
        case 28: return "chara/new_player/FORM05/1P_00_eye";
        case 29: return "chara/new_player/FORM05/2P_00_eye";
        case 30: return "chara/new_player/FORM05/1P_01_eye";
        case 31: return "chara/new_player/FORM05/2P_01_eye";
        case 32: return "chara/new_player/FORM05/ADD_PARTS";
        case 33: return "chara/new_player/FORM05/ITEM";
        case 34: return "chara/new_player/FORM07/BODY";
        case 35: return "chara/new_player/FORM07/1P_eye";
        case 36: return "chara/new_player/FORM07/2P_eye";
        case 37: return "chara/new_player/FORM11/BODY";
        case 38: return "chara/new_player/FORM11/1P_eye";
        case 39: return "chara/new_player/FORM11/2P_eye";
        case 40: return "chara/new_player/FORM11/STAR";
        case 41: return "chara/new_player/FORM12/BODY";
        case 42: return "chara/new_player/FORM12/STAR";
        case 43: return "chara/new_player/FORM12/STAR01";
        case 44: return "chara/new_player/FORM12/1P_eye";
        case 45: return "chara/new_player/FORM12/2P_eye";
        case 46: return "chara/new_player/FORM13/BODY";
        case 47: return "chara/new_player/FORM13/STAR";
        case 48: return "chara/new_player/FORM13/CROWN";
        case 49: return "chara/new_player/FORM13/1P_eye";
        case 50: return "chara/new_player/FORM13/2P_eye";
        case 51: return "chara/new_player/FORM14/FORM14";
        case 52: return "chara/new_player/FORM14/1P_eye";
        case 53: return "chara/new_player/FORM14/2P_eye";
        case 54: return "chara/env/PlayGuideIcon";
        default: return (const char*)id; // ...why?
    }
}

PlTransResMng::PlTransResMng() { }

PlTransResMng::~PlTransResMng() { }
