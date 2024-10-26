#ifndef FLUFF_GIMMICKLIST_H
#define FLUFF_GIMMICKLIST_H

#include "types.h"

// [ID label] = [ID number] // [is common]

// A large portion of these Gimmick names are written in Japanese.

ENUM_CLASS(GimmickIDs,
    Invalid = -1,
    None = 0,
    GMK_TYPE_SIMPLE_MDL = 1,        // common
    SimpleMdlCommon = 2,            // common
    SimpleMdlGmk    = 3,            // common
    SimpleNurbsCommon = 4,          // common
    SimpleNurbsGmk  = 5,            // common
    ColAnimMdl      = 6,            // common
    ForceAsyncLoad  = 7,
    BGAsyncBlockNum = 8,
    Effect          = 9,
    ShadowNw4rOffset = 10,
    ShadowItoOffset = 11,
    CamCtrl         = 12,
    CompulsoryCamera = 13,          
    CameraRectangleControl = 14,    
    CameraZoom      = 15,           
    CameraTemporaryZoom = 16,       
    MultiCamPriorityCtrl = 17,
    EnemyGenerator  = 18,           
    PreviewBgLoad   = 19,
    PreviewBackDrop = 20,
    Bead_Small_White = 21,          // common
    Bead_Small_Blue  = 22,          // common
    Bead_Small_Green = 23,          // common
    Bead_Small_Orange = 24,         // common
    Bead_Small_Red   = 25,          // common
    Bead_Small_Purple = 26,         // common
    Bead_Small_Yellow = 27,         // common
    Bead_Medium_White = 28,              // common
    Bead_Medium_Blue = 29,               // common
    Bead_Medium_Green = 30,              // common
    Bead_Medium_Orange = 31,             // common
    Bead_Medium_Red = 32,                // common
    Bead_Medium_Purple = 33,             // common
    Bead_Medium_Yellow = 34,             // common
    Bead_Large_White = 35,               // common
    Bead_Large_Blue = 36,                // common
    Bead_Large_Green = 37,               // common
    Bead_Large_Orange = 38,              // common
    Bead_Large_Red = 39,                 // common
    Bead_Large_Purple = 40,              // common
    Bead_Large_Yellow = 41,              // common
    Bead_ExtraLarge = 42,                // common
    BeadHolder,
    TurnCloth,                      
    Thumbtack,                      
    PendulumButton,                 
    JumpButton,                     
    PullOutButton01,                
    PullOutButton02,                 
    PullOutButton03,                
    MobileScaffold_Small,            
    MobileScaffold_Large,            
    Curtains,                       
    HappyGate_Goal,                 
    TreasureChest,                

    DecorativeBall = 0x102,
      
    GimmickTypeCount = 0x1B3
);
#endif
