#ifndef NW4R_G3D_RESANMLIGHT_H
#define NW4R_G3D_RESANMLIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

// Forward declarations
struct LightAnmResult;

struct ResAnmLightDataTypedef {
    enum LightType {
        LIGHTTYPE_POINT,
        LIGHTTYPE_DIRECTIONAL,
        LIGHTTYPE_SPOT,

        LIGHTTYPE_MAX
    };

    enum Flag {
        FLAG_LIGHT_TYPE_MASK = (1 << 0) | (1 << 1),
        FLAG_ENABLE = (1 << 2),
        FLAG_SPECULAR = (1 << 3),

        // TODO: Naming
        FLAG_4 = (1 << 4),
        FLAG_5 = (1 << 5),

        FLAG_POS_X_CONSTANT = (1 << 19),
        FLAG_POS_Y_CONSTANT = (1 << 20),
        FLAG_POS_Z_CONSTANT = (1 << 21),

        FLAG_COLOR_CONSTANT = (1 << 22),
        FLAG_ENABLE_CONSTANT = (1 << 23),

        FLAG_AIM_X_CONSTANT = (1 << 24),
        FLAG_AIM_Y_CONSTANT = (1 << 25),
        FLAG_AIM_Z_CONSTANT = (1 << 26),

        FLAG_CUTOFF_CONSTANT = (1 << 27),
        FLAG_REF_DISTANCE_CONSTANT = (1 << 28),
        FLAG_REF_BRIGHTNESS_CONSTANT = (1 << 29),
        FLAG_SPEC_COLOR_CONSTANT = (1 << 30),
        FLAG_SHININESS_CONSTANT = (1 << 31),

        // Flags accessible from LightAnmResult
        FLAG_ANM_RESULT_MASK =
            FLAG_LIGHT_TYPE_MASK | FLAG_ENABLE | FLAG_SPECULAR | FLAG_4 | FLAG_5
    };
};

struct ResAnmLightData : ResAnmLightDataTypedef {
    u32 size;                  // at 0x0
    s32 toResAnmScnData;       // at 0x4
    s32 name;                  // at 0x8
    u32 id;                    // at 0xC
    u32 refNumber;             // at 0x10
    u32 specLightObjIdx;       // at 0x14
    s32 toResUserData;         // at 0x18
    u32 flags;                 // at 0x1C
    ResBoolAnmData enable;     // at 0x20
    ResAnmData posX;           // at 0x24
    ResAnmData posY;           // at 0x28
    ResAnmData posZ;           // at 0x2C
    ResColorAnmData color;     // at 0x30
    ResAnmData aimX;           // at 0x34
    ResAnmData aimY;           // at 0x38
    ResAnmData aimZ;           // at 0x3C
    GXDistAttnFn distFunc;     // at 0x40
    ResAnmData refDistance;    // at 0x44
    ResAnmData refBrightness;  // at 0x48
    GXSpotFn spotFunc;         // at 0x4C
    ResAnmData cutoff;         // at 0x50
    ResColorAnmData specColor; // at 0x54
    ResAnmData shininess;      // at 0x58
};

class ResAnmLight : public ResCommon<ResAnmLightData>,
                    public ResAnmLightDataTypedef {
public:
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmLight);

    void GetAnmResult(LightAnmResult* pResult, f32 frame) const;

    u32 GetID() const {
        return ref().id;
    }

    u32 GetRefNumber() const {
        return ref().refNumber;
    }

    u32 GetSpecularLightIdx() const {
        return ref().specLightObjIdx;
    }

    bool HasSpecularLight() const {
        return ref().flags & FLAG_SPECULAR;
    }
};

} // namespace g3d
} // namespace nw4r

#endif