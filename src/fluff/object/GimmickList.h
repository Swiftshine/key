#ifndef FLUFF_GIMMICKLIST_H
#define FLUFF_GIMMICKLIST_H

#include "types.h"

// todo - fill this out later (and rename enumerations to class names instead)

// [ID label] = [ID number] // [is common]

// A large portion of these Gimmick names are written in Japanese.

enum GimmickID {
    eGimmickID_Invalid = -1,
    eGimmickID_None = 0,
    eGimmickID_GMK_TYPE_SIMPLE_MDL = 1,        // common
    eGimmickID_SimpleMdlCommon = 2,            // common

    eGimmickID_GmkSimpleMdl    = 3,            // common

    eGimmickID_SimpleNurbsCommon = 4,          // common
    eGimmickID_SimpleNurbsGmk  = 5,            // common
    eGimmickID_ColAnimMdl      = 6,            // common
    eGimmickID_ForceAsyncLoad  = 7,
    eGimmickID_BGAsyncBlockNum = 8,
    eGimmickID_Effect          = 9,
    eGimmickID_ShadowNw4rOffset = 10,
    eGimmickID_ShadowItoOffset = 11,
    eGimmickID_CamCtrl         = 12,
    eGimmickID_CompulsoryCamera = 13,
    eGimmickID_CameraRectangleControl = 14,
    eGimmickID_CameraZoom      = 15,
    eGimmickID_CameraTemporaryZoom = 16,
    eGimmickID_MultiCamPriorityCtrl = 17,
    eGimmickID_EnemyGenerator  = 18,
    eGimmickID_PreviewBgLoad   = 19,
    eGimmickID_PreviewBackDrop = 20,
    eGimmickID_Bead_Small_White = 21,          // common
    eGimmickID_Bead_Small_Blue  = 22,          // common
    eGimmickID_Bead_Small_Green = 23,          // common
    eGimmickID_Bead_Small_Orange = 24,         // common
    eGimmickID_Bead_Small_Red   = 25,          // common
    eGimmickID_Bead_Small_Purple = 26,         // common
    eGimmickID_Bead_Small_Yellow = 27,         // common
    eGimmickID_Bead_Medium_White = 28,              // common
    eGimmickID_Bead_Medium_Blue = 29,               // common
    eGimmickID_Bead_Medium_Green = 30,              // common
    eGimmickID_Bead_Medium_Orange = 31,             // common
    eGimmickID_Bead_Medium_Red = 32,                // common
    eGimmickID_Bead_Medium_Purple = 33,             // common
    eGimmickID_Bead_Medium_Yellow = 34,             // common
    eGimmickID_Bead_Large_White = 35,               // common
    eGimmickID_Bead_Large_Blue = 36,                // common
    eGimmickID_Bead_Large_Green = 37,               // common
    eGimmickID_Bead_Large_Orange = 38,              // common
    eGimmickID_Bead_Large_Red = 39,                 // common
    eGimmickID_Bead_Large_Purple = 40,              // common
    eGimmickID_Bead_Large_Yellow = 41,              // common
    eGimmickID_Bead_ExtraLarge = 42,                // common
    eGimmickID_BeadHolder,
    eGimmickID_TurnCloth,
    eGimmickID_Thumbtack,
    eGimmickID_PendulumButton,
    eGimmickID_JumpButton,
    eGimmickID_PullOutButton01,
    eGimmickID_PullOutButton02,
    eGimmickID_PullOutButton03,
    eGimmickID_MobileScaffold_Small,
    eGimmickID_MobileScaffold_Large,
    eGimmickID_Curtains,
    eGimmickID_HappyGate_Goal,
    eGimmickID_TreasureChest,

    eGimmickID_GmkUpdownWater = 0x61,
    eGimmickID_GmkTurtle = 0x8D,

    eGimmickID_DecorativeBall = 0x102,

    GIMMICK_TYPE_COUNT = 0x1B3
};
#endif
