#include "manager/GameManager.h"

GameManager::GameManager() { }


PointerManagerWrapper::PointerManagerWrapper()
    : mManager(nullptr)
{ }

PointerManagerWrapper::~PointerManagerWrapper() {
    delete mManager;
    mManager = nullptr;
}

GameManager::~GameManager() { }

uint GameManager::GetPlayerCount() {
    if (sInstance) {
        return sInstance->mPlayerCount;
    }

    return 0;
}

PlayerBase* GameManager::GetPlayerByID(uint playerID) {
    if (!GameManager::sInstance) {
        return nullptr;
    }
    
    // we're trying to get Prince Fluff, but he doesn't exist
    if (PlayerBase::PlayerID::PrinceFluff == playerID && GameManager::GetPlayerCount() == 1) {
        return nullptr;
    }

    return GameManager::sInstance->mPlayers[playerID];
} 

PlayerBase* GameManager::GetPrinceFluff() {
    if (GameManager::sInstance) {
        return GameManager::sInstance->mPlayers[PlayerBase::PlayerID::PrinceFluff];
    }

    return nullptr;
}


u8 GameManager::GetByte(uint val) {
    return val & 0xFF;
}

PointerManagerWrapper GameManager::GetPlayerPointerManagerWrapperByID(uint id) {
    return GameManager::sInstance->mPlayerPointerManagers[id];
}
