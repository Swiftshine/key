#ifndef FLUFF_FRIENDEFFECT_H
#define FLUFF_FRIENDEFFECT_H

#include "graphics/FlfMdlDraw.h"

#define NUM_FRIEND_TYPES 5

class FriendEffect {
public:
    FriendEffect();
    ~FriendEffect();

    /* Class Methods */

    void UpdateFrame();
    void SetWoolDrawMatrix(const nw4r::math::MTX34&);
    bool IsAnimationDone() DONT_INLINE_CLASS;
    void ResetNURBSFrame();
    void SetVisibility(bool vis);
    void Reset(int id);

    /* Static Methods */
    static void AddResources();

    /* Class Members */

    int mFriendID;
    FlfMdlDraw* mEffects[NUM_FRIEND_TYPES];
};

#endif
