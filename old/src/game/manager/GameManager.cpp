#include <game/manager/GameManager.h>

GameManager::GameManager() {

}


PointerManagerWrapper::PointerManagerWrapper()
    : mgr(NULL)
{ }

PointerManagerWrapper::~PointerManagerWrapper() {
    delete mgr;
    mgr = NULL;
}



GameManager::~GameManager() {

}

u32 GameManager::GetPlayerCount() {
    if (GameManager::Instance) {
        return GameManager::Instance->playerCount;
    }

    return 0;
}

PlayerBase* GameManager::GetPlayerByID(u32 playerID) {
    if (!GameManager::Instance) {
        return NULL;
    }
    
    // we're trying to get Prince Fluff, but he doesn't exist
    if (PlayerBase::PlayerIDs::PrinceFluff == playerID && GameManager::GetPlayerCount() == 1) {
        return NULL;
    }

    return GameManager::Instance->players[playerID];
} 

PlayerBase* GameManager::GetPrinceFluff() {
    if (GameManager::Instance) {
        return GameManager::Instance->players[PlayerBase::PlayerIDs::PrinceFluff];
    }

    return NULL;
}


u8 GameManager::GetByte(u32 val) {
    return val & 0xFF;
}

PointerManagerWrapper GameManager::GetPlayerPointerManagerWrapperByID(u32 id) {
    return GameManager::Instance->playerPointerManagers[id];
}
