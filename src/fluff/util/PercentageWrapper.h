#ifndef FLUFF_PERCENTAGEWRAPPER_H
#define FLUFF_PERCENTAGEWRAPPER_H

// ?

/// @note Size: `0x20`
struct PercentageWrapper {
    void Reset();
    void SetDefault();
    void Update();

    /* Members */

    s32 m_0;
    f32 m_4;
    f32 m_8;
    f32 m_C;
    f32 m_10;
    f32 m_14;
    f32 m_18;
    bool mUpdate;
};

#endif
