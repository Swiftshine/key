#ifndef FLUFF_MISSIONINFO_H
#define FLUFF_MISSIONINFO_H

struct MissionInfo {
    /* 0x0 */ int m_0;
    /// @brief The number of actions needed to be done in order for the mission to be successful.
    /* 0x4 */ int mCompletionThreshold;
};

#endif