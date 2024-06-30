#include <game/manager/GimmickManager.h>

GimmickManager::GimmickManager() {
    GimmickManager::Instance = this;
}

GimmickManager::~GimmickManager() {
    GimmickManager::Instance = NULL;
}

void GimmickManager::AddGimmick(Gimmick* gmk) {

}

void GimmickManager::RemoveGimmick(Gimmick* gmk) {
    
}

void GimmickManager::SetupGimmicks() { }

void GimmickManager::SetMapbin(Mapdata::Mapbin::Header* header) {
    mapbin = header;
    _4 = 0;
    _0 = 1;
}

void GimmickManager::ClearGimmicks(int unk) { }
