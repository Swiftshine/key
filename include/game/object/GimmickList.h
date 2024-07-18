#ifndef FLUFF_GIMMICK_LIST_H
#define FLUFF_GIMMICK_LIST_H

const int MAX_GIMMICK_TYPES = 0x1B2;

// [id label] = [id number] // "japanese string", [is common]

// entries are written as they appear unless indicated otherwise (e.g., japanese string in a comment)

typedef enum GimmickID {
    Invalid = -1,
    None = 0,
    GMK_TYPE_SIMPLE_MDL = 1,
    SimpleMdlCommon = 2,            // common
    SimpleMdlGmk    = 3,            // common
    SimpleNurbsCommon = 4,          // common
    SimpleNurbsGmk  = 5,            // common
    ColAnimMdl      = 6,            // common
    ForceAsyncLoad  = 7,
    BGAsyncBlockNum = 8,
    Effect          = 9,            // "エフェクト"
    ShadowNw4rOffset = 10,
    ShadowItoOffset = 11,
    CamCtrl         = 12,
    CompulsoryCamera = 13,          // "強制カメラ"
    CameraRectangleControl = 14,    // "カメラ矩形制御"
    CameraZoom      = 15,           // "カメラズーム"
    CameraTemporaryZoom = 16,       // "カメラ一時ズーム"
    MultiCamPriorityCtrl = 17,
    EnemyGenerator  = 18,           // "敵生成",
    PreviewBgLoad   = 19,
    PreviewBackDrop = 20,
    Bead_Small_White = 21,          // "ビーズ（小）白", common
    Bead_Small_Blue  = 22,          // "ビーズ（小）青", common
    Bead_Small_Green = 23,          // "ビーズ（小）緑", common
    Bead_Small_Orange = 24,         // "ビーズ（小）橙", common
    Bead_Small_Red   = 25,          // "ビーズ（小）赤", common
    Bead_Small_Purple = 26,         // "ビーズ（小）紫", common
    Bead_Small_Yellow = 27,         // "ビーズ（小）黄", common
    Bead_Medium_White,              // "ビーズ (中) 白", common
    Bead_Medium_Blue,               // "ビーズ (中) 青", common
    Bead_Medium_Green,              // "ビーズ (中) 緑", common
    Bead_Medium_Orange,             // "ビーズ (中) 橙", common
    Bead_Medium_Red,                // "ビーズ (中) 赤", common
    Bead_Medium_Purple,             // "ビーズ (中) 紫", common
    Bead_Medium_Yellow,             // "ビーズ (中) 黄", common
    Bead_Large_White,               // "ビーズ (大) 白", common
    Bead_Large_Blue,                // "ビーズ (大) 青", common
    Bead_Large_Green,               // "ビーズ (大) 緑", common
    Bead_Large_Orange,              // "ビーズ (大) 橙", common
    Bead_Large_Red,                 // "ビーズ (大) 赤", common
    Bead_Large_Purple,              // "ビーズ (大) 紫", common
    Bead_Large_Yellow,              // "ビーズ (大) 黄", common
    Bead_ExtraLarge,                // "ビーズ（特大）", common
    BeadHolder,
    TurnCloth,                      // "めくれ布"
    Thumbtack,                      // "鋲"
    PendulumButton,                 // "振り子ボタン"
    JumpButton,                     // "ジャンプボタン"
    PullOutButton01,                // "引き抜きボタン01"
    PullOutButton02,                // "引き抜きボタン02"
    PullOutButton03,                // "引き抜きボタン03"
    MobileScaffold_Small,           // "移動足場（小）"
    MobileScaffold_Large,           // "移動足場（大）"
    Curtains,                       // "カーテン"
    HappyGate_Goal,                 // "ハッピーゲート（ゴール）"
    TreasureChest,                  // "宝箱"
    
    
} GimmickID;
#endif
