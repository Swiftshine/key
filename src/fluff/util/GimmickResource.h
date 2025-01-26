#ifndef FLUFF_GIMMICKRESOURCE_H
#define FLUFF_GIMMICKRESOURCE_H

#include "object/Gimmick.h"
#include "gfl/gflLinkedList.h"
#include <string>

// a structure for keeping track of gimmicks that use a particular resource
// size: 0x1C
class GimmickResource {
public:
    GimmickResource(const char* resName);
    ~GimmickResource();
    void RegisterGimmick(Gimmick* gimmick);
    void Clear();

    inline std::string& GetResourceName() {
        return mResourceName;
    }
private:
    std::string mResourceName; // @ 0x0, size: 0xC
    bool m_C;
    gfl::LinkedList<FlfHandle> mGimmickHandles; // @ 0x10, size: 0x1C
};

#endif
