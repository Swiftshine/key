#ifndef FLUFF_GIMMICK_MANAGER_H
#define FLUFF_GIMMICK_MANAGER_H

#include <gfl/task.h>
#include <game/object/Gimmick.h>

class GimmickManager {
private:
    GimmickManager();
    ~GimmickManager();
public:
    static GimmickManager* Instance;

    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
};
#endif
