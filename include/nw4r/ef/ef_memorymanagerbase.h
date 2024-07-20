#ifndef NW4R_EF_MEMORYMANAGERBASE
#define NW4R_EF_MEMORYMANAGERBASE
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		struct MemoryManagerBase
		{
			virtual ~MemoryManagerBase(); // at 0x8
			virtual UNKTYPE GarbageCollection() = 0; // at 0xc
			
			virtual Effect * AllocEffect() = 0; // at 0x10
			virtual UNKTYPE FreeEffect(void *) = 0; // at 0x14
			virtual u32 GetNumAllocEffect() const = 0; // at 0x18
			virtual u32 GetNumActiveEffect() const = 0; // at 0x1c
			virtual u32 GetNumFreeEffect() const = 0; // at 0x20
			
			virtual Emitter * AllocEmitter() = 0; // at 0x24
			virtual UNKTYPE FreeEmitter(void *) = 0; // at 0x28
			virtual u32 GetNumAllocEmitter() const = 0; // at 0x2c
			virtual u32 GetNumActiveEmitter() const = 0; // at 0x30
			virtual u32 GetNumFreeEmitter() const = 0; // at 0x34
			
			virtual ParticleManager * AllocParticleManager() = 0; // at 0x38
			virtual UNKTYPE FreeParticleManager(void *) = 0; // at 0x3c
			virtual u32 GetNumAllocParticleManager() const = 0; // at 0x40
			virtual u32 GetNumActiveParticleManager() const = 0; // at 0x44
			virtual u32 GetNumFreeParticleManager() const = 0; // at 0x48
			
			virtual Particle * AllocParticle() = 0; // at 0x4c
			virtual UNKTYPE FreeParticle(void *) = 0; // at 0x50
			virtual u32 GetNumAllocParticle() const = 0; // at 0x54
			virtual u32 GetNumActiveParticle() const = 0; // at 0x58
			virtual u32 GetNumFreeParticle() const = 0; // at 0x5c
			
			virtual void * AllocHeap(u32) = 0; // at 0x60
		};
	}
}

#endif
