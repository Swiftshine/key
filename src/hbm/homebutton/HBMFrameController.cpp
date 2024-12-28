#include "HBMFrameController.hpp"

/*******************************************************************************
 * headers
 */

#include <types.h> // f32

#include <hbm/context_rvl.h>

/*******************************************************************************
 * functions
 */

namespace homebutton {

void FrameController::init(int anm_type, f32 max_frame, f32 min_frame, f32 delta)
{
	OSAssert_Line(21, eAnmType_Forward <= anm_type && anm_type < eAnmType_Max);
	OSAssert_Line(22, max_frame > min_frame && min_frame >= 0.0f);
	OSAssert_Line(23, delta > 0.0f);

	mAnmType = anm_type;
	mMaxFrame = max_frame;
	mMinFrame = min_frame;

	mFrameDelta = delta;
	mState = eState_Stopped;
	mAltFlag = false;

	// initFrame();
	OSAssert_Line(40, mMinFrame <= mMaxFrame);

	mCurFrame = mAnmType == eAnmType_Backward ? mMaxFrame : mMinFrame;
}

void FrameController::initFrame()
{
	OSAssert_Line(40, mMinFrame <= mMaxFrame);

	mCurFrame = mAnmType == eAnmType_Backward ? mMaxFrame : mMinFrame;
}

void FrameController::calc()
{
	if (mState != eState_Playing)
		return;

	switch (mAnmType)
	{
	case eAnmType_Forward:
		if ((mCurFrame += mFrameDelta) >= getLastFrame())
		{
			mCurFrame = getLastFrame();
			stop();
		}

		break;

	case eAnmType_Backward:
		if ((mCurFrame -= mFrameDelta) <= mMinFrame)
		{
			mCurFrame = mMinFrame;
			stop();
		}

		break;

	case eAnmType_Wrap:
		if ((mCurFrame += mFrameDelta) >= mMaxFrame)
			mCurFrame -= mMaxFrame - mMinFrame;

		break;

	case eAnmType_Oscillate:
		if (!mAltFlag)
		{
			if ((mCurFrame += mFrameDelta) >= getLastFrame())
			{
				mCurFrame = getLastFrame();
				mAltFlag = true;
			}
		}
		else
		{
			if ((mCurFrame -= mFrameDelta) <= mMinFrame)
			{
				mCurFrame = mMinFrame;
				mAltFlag = false;
			}
		}

		break;
	}
}

} // namespace homebutton
