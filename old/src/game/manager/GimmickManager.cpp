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
    mpMapbin = header;
    m_4 = 0;
    m_0 = 1;
}

void GimmickManager::ClearAll(bool clearMapdata) {
    // while (gimmicks.entries) {
    //     delete gimmicks.last->data;
    // }
}
