#ifndef FLUFF_SPRINGBASE_H
#define FLUFF_SPRINGBASE_H

#include "object/FlfGameObj.h"
#include "graphics/KeyFrame.h"
#include "gfl/gflArray.h"

// size: 0x150
class SpringBase : public FlfGameObj {
public:
    class Spring {

    };

    class Particle {
    public:
        Particle();
        ~Particle();
    };
public:
    SpringBase(u32, const char* taskName);
    virtual ~SpringBase();

    /* SpringBase */

    virtual void vf68();
    virtual float GetZPos();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
private:
    gfl::Task mTask;
    int m_98;
    int m_9C;
    gfl::Array<Particle> mParticles;
    int m_A4;
    int m_A8;
    int m_AC;
    int m_B0;
    int m_B4;
    KeyFrame<float> mKeyFrame1;
    bool m_D0;
    KeyFrame<float> mKeyFrame2;
    bool m_EC;
    KeyFrame<float> mKeyFrame3;
    bool m_108;
    int m_10C;
    float m_110;
    float m_114;
    float m_118;
    float m_11C;
    float m_120;
    float m_124;
    float m_128;
    float m_12C;
    float m_130;
    float m_134;
    float m_138;
    float m_13C;
    float m_140;
    int m_144;
    int m_148;
    int m_148;
};

ASSERT_SIZE(SpringBase, 0x150);

#endif
