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

u32 GameManager::GetPlayerCount() {
    if (sInstance != nullptr) {
        return sInstance->mPlayerCount;
    }

    return 0;
}

PlayerBase* GameManager::GetPlayerByID(u32 playerID) {
    if (GameManager::sInstance == nullptr) {
        return nullptr;
    }

    // we're trying to get Prince Fluff, but he doesn't exist
    if (PlayerBase::ePlayerID_PrinceFluff == playerID && GameManager::GetPlayerCount() == 1) {
        return nullptr;
    }

    return GameManager::sInstance->mPlayers[playerID];
}

PlayerBase* GameManager::GetPrinceFluff() {
    if (GameManager::sInstance != nullptr) {
        return GameManager::sInstance->mPlayers[PlayerBase::ePlayerID_PrinceFluff];
    }

    return nullptr;
}


u8 GameManager::GetByte(u32 val) {
    return val & 0xFF;
}

PointerManagerWrapper GameManager::GetPlayerPointerManagerWrapperByID(u32 id) {
    return GameManager::sInstance->mPlayerPointerManagers[id];
}
