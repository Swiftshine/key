#ifndef RVL_SDK_HBM_HOMEBUTTON_AX_SOUND_HPP
#define RVL_SDK_HBM_HOMEBUTTON_AX_SOUND_HPP

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "../sound/mix.h" // HBMMIXSoundMode

/*******************************************************************************
 * classes and functions
 */

namespace homebutton
{
	void PlaySeq(int num);
	void InitAxSound(const void *soundData, void *mem, u32 memSize);
	void ShutdownAxSound();
	void AxSoundMain();
	void StopAllSeq();
	void SetVolumeAllSeq(f32 gain);
	void SetSoundMode(HBMMIXSoundMode mode);
} // namespace homebutton

#endif // RVL_SDK_HBM_HOMEBUTTON_AX_SOUND_HPP
