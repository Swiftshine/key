#include <game/object/Gimmick.h>
#include <game/manager/GimmickManager.h>
#include <gfl/functor/FunctorClassMethod.h>

typedef gfl::FunctorClassMethod0<void, Gimmick, void(Gimmick::*)(void)>;

Gimmick::Gimmick(u32 gmkID)
    : FlfGameObj(FlfGameObjTypes::Gimmick)
    , gimmickID(static_cast<GimmickID>(gmkID))
    , _84(0)

{    
    _124 = 0;
    task = NULL;
    _12C = NULL;
    
    GimmickManager::Instance->AddGimmick(this);
    fn_8004EC4C();
}

Gimmick::Gimmick(u32 gmkID, const char* taskName)
    : FlfGameObj(FlfGameObjTypes::Gimmick)
    , gimmickID(static_cast<GimmickID>(gmkID))
    , _84(0)
{
    _124 = 0;
    task = NULL;
    _12C = NULL;

    task = new gfl::Task();
    if (task) {
        task->Init(taskName);
    } else {
        delete task;
        task = NULL;
    }
    if (!task) {
        delete task;
        task = NULL;
    }

    GimmickManager::Instance->AddGimmick(this);
}

void Gimmick::vfB0__7GimmickFv() { /*(this->*state1)();*/ return; }

// Gimmick::Gimmick(u32 gmkID, const char* taskName)
//     : FlfGameObj(FlfGameObjTypes::Gimmick)
// {
//     GimmickManager::Instance->AddGimmick(this);
// }

// Gimmick::Gimmick(StageTask* stageTask, const char* taskName)
//     : FlfGameObj(FlfGameObjTypes::Gimmick)
// {
//     GimmickManager::Instance->AddGimmick(this);
// }



// Gimmick::Gimmick(u32 gmkID, StageTask* stageTask) 
//     : FlfGameObj(FlfGameObjTypes::Gimmick) 
// {
//     GimmickManager::Instance->AddGimmick(this);
// }

// Gimmick::~Gimmick() {  
//     GimmickManager::Instance->RemoveGimmick(this);

//     fn_8004ED1C();
    
//     if (_84) {
//         u32 unk = *(u32*)(_84 + 0x98);
//         if (unk) {
//             *(u32*)(unk + 4) = 0;
//         }
//     }

//     if (task2) {
//         delete task2;
//     }

//     task2 = NULL;

//     if (_124) {
//         // is a dtor but idk of what
//         fn_8051F7A0(_124, 1);
//     }
//     _124 = NULL;


// }

// void Gimmick::vfB0__7GimmickFv() { /* virtual */ }

// // void Gimmick::fn_8004ED1C() { _12C = 0; }

