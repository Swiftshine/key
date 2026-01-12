#ifndef FLUFF_PERCENTAGEWRAPPER_H
#define FLUFF_PERCENTAGEWRAPPER_H

// ?

/// @note Size: `0x20`
struct PercentageWrapper {
    void Reset();
    void SetDefault();
    void Update();

    /* Members */

    int m_0;
    float m_4;
    float m_8;
    float m_C;
    float m_10;
    float m_14;
    float m_18;
    bool mUpdate;
};

#endif