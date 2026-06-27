#ifndef FLUFF_RESOURCEMANAGER_H
#define FLUFF_RESOURCEMANAGER_H

class ResourceManager {
private:
    static ResourceManager* sInstance;
public:
    static inline ResourceManager* Instance() {
        return sInstance;
    }

    void AddCharaResourceName(const char* pResourceName);
};

#endif
