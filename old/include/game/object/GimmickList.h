#ifndef FLUFF_GIMMICK_LIST_H
#define FLUFF_GIMMICK_LIST_H

#include <flf_types.h>

const int MAX_GIMMICK_TYPES = 0x1B2;

// [id label] = [id number] // "japanese string", [is common]

// entries are written as they appear unless indicated otherwise (e.g., japanese string in a comment)

SCOPED_ENUM (GimmickIDs,

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
    Bead_Medium_White,              // common
    Bead_Medium_Blue,               // common
    Bead_Medium_Green,              // common
    Bead_Medium_Orange,             // common
    Bead_Medium_Red,                // common
    Bead_Medium_Purple,             // common
    Bead_Medium_Yellow,             // common
    Bead_Large_White,               // common
    Bead_Large_Blue,                // common
    Bead_Large_Green,               // common
    Bead_Large_Orange,              // common
    Bead_Large_Red,                 // common
    Bead_Large_Purple,              // common
    Bead_Large_Yellow,              // common
    Bead_ExtraLarge,                // common
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
);

#endif

namespace dummy { }
