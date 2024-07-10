// #include <game/object/Gimmick.h>
// #include <game/manager/GimmickManager.h>

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


// Gimmick::Gimmick(u32 gmkID)
//     : FlfGameObj(FlfGameObjTypes::Gimmick)
//     , id(gmkID)
//     , _84(0)
//     , _88(-1)
//     , _8C()
//     , _98()

//     , _B0(6)
//     , _B4(4)
//     , _B8(0)

//     , _A4(false)
//     , _AC(65)

//     , _124(0)
//     , task2(NULL)
//     , _120(0)
// {
    

//     for (int i = 0; i < 5; i++) {
//         // _BC[i] = 0;
//         // _D0[i] = 0.0f;
//         strings[i].begin = "";
//     }


//     GimmickManager::Instance->AddGimmick(this);
//     fn_8004EC4C();
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

// void Gimmick::fn_8004DF54() { /* virtual */ }

// // void Gimmick::fn_8004ED1C() { _12C = 0; }
