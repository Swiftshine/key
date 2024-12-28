#include "HBMAnmController.hpp"

/*******************************************************************************
 * headers
 */

#include <macros.h> // NW4HBM_RANGE_FOR

#include "../nw4hbm/lyt/lyt_animation.hpp"
#include "../nw4hbm/lyt/lyt_group.hpp"
#include "../nw4hbm/lyt/lyt_pane.hpp"

#include "../nw4hbm/ut/ut_LinkList.hpp" // IWYU pragma: keep (NW4HBM_RANGE_FOR)

/*******************************************************************************
 * functions
 */

namespace homebutton {

GroupAnmController::GroupAnmController():
	mpGroup			(),
	mpAnimGroup		()
{}

GroupAnmController::~GroupAnmController() {}

void GroupAnmController::do_calc()
{
	bool flag;

	if (mState == eState_Playing)
	{
		calc();
		flag = true;

		mpAnimGroup->SetFrame(mCurFrame);
	}
	else
	{
		flag = false;
	}

	nw4hbm::lyt::detail::PaneLink::LinkList &list = mpGroup->GetPaneList();

	NW4HBM_RANGE_FOR(it, list)
		it->mTarget->SetAnimationEnable(mpAnimGroup, flag, false);
}

} // namespace homebutton
