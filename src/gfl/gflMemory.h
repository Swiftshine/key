#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include <revolution/os.h>
#include "gflMemoryBase.h"

extern "C" OSMutex BPEMutex;

namespace gfl {
    class Memory : public MemoryBase {
    private:
        static Memory* sInstance;
        static bool sIsInited;
        static OSMutex* sCurrentMutex;
    public:
        static Memory* InitInstance();

        inline Memory() { }
        static inline Memory* Instance() { return sInstance; }
        static inline Memory* TryGetInstance() {
            Memory* m = Instance();

            if (!m) {
                m = InitInstance();
            } else {
                m = Instance();
            }

            return m;
        }
        static inline bool IsInited() { return sIsInited; }
        static inline void SetInited(bool inited) { sIsInited = inited; }
        static OSMutex* ValidateHeapMutex(u8 searchID, OSMutex* mutex, u8 maxID);
        static inline void SetCurrentMutex(OSMutex* mutex) { sCurrentMutex = mutex; }
        static inline OSMutex* GetCurrentMutex() { return sCurrentMutex; }

        static inline void CheckInit() {
            if (!sIsInited) {
                InitInstance();
                OSMutex* mutex;
                mutex = ValidateHeapMutex(0x18, &BPEMutex, 0x18);
                
                if (nullptr != mutex) {
                    OSInitMutex(mutex);
                }

                SetCurrentMutex(mutex);
                SetInited(true);
            }
        }

        static inline void InitIfNotInited() {
            if (nullptr == Instance()) {
                InitInstance();
            }
        }

        inline Heap* GetLIB1Heap() { return &mLIB1Heap; }
        inline Heap* GetLIB2Heap() { return &mLIB2Heap; }
        inline Heap* GetStringHeap() { return &mStringHeap; }
        inline Heap* GetEtcHeap() { return &mEtcHeap; }
        inline Heap* GetSoundHeap() { return &mSoundHeap; }

        void SetupHeaps();
    private:
        Heap mLIB1Heap;
        Heap mLIB2Heap;
        Heap mStringHeap;
        Heap mEtcHeap;
        Heap mSoundHeap;
    };


    ASSERT_SIZE(Memory, 0x1B8);
}

#endif