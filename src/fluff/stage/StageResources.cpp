#include "stage/StageResources.h"

// https://decomp.me/scratch/gQrVX
StageResources::StageResources() {
    sInstance = this;
}

StageResources::~StageResources() {
    sInstance = nullptr;
}
