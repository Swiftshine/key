#ifndef GFL_MUTEX_H
#define GFL_MUTEX_H

#include <revolution/OS.h>

namespace gfl {

class Mutex : public OSMutex {
public:
    Mutex() {
        OSInitMutex(this);
    }

    void Lock() {
        OSLockMutex(this);
    }

    void Unlock() {
        OSUnlockMutex(this);
    }
};

}
#endif
