#include "gflResInfo.h"

void gfl::ResInfo::IncrementRefCount() {
    mRefCount.IncrementRefCount();
}