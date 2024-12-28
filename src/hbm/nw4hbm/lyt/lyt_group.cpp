#include "lyt_group.hpp"

/*******************************************************************************
 * headers
 */

#include <new>
#include <cstring> // std::memcpy

#include <macros.h>
#include <types.h>

#include "lyt_common.hpp" // detail::EqualsPaneName
#include "lyt_layout.hpp"
#include "lyt_pane.hpp"
#include "lyt_types.hpp" // detail::ConvertOffsToPtr

#include "../ut/ut_LinkList.hpp" // IWYU pragma: keep (NW4HBM_RANGE_FOR)

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace lyt {

Group::Group(const res::Group *pResGroup, Pane *pRootPane)
{
	Init();
	std::memcpy(&mName, &pResGroup->name, sizeof mName);

	const char *paneName =
		detail::ConvertOffsToPtr<char>(pResGroup, sizeof *pResGroup);

	for (int i = 0; i < pResGroup->paneNum; i++)
	{
		Pane *pFindPane = pRootPane->FindPaneByName(
			paneName + (int)sizeof pResGroup->name * i, true);

		if (pFindPane)
			AppendPane(pFindPane);
	}
}

void Group::Init()
{
	mbUserAllocated = false;
}

Group::~Group()
{
	NW4HBM_RANGE_FOR_NO_AUTO_INC(it, mPaneLinkList)
	{
		decltype(it) currIt = it++;

		mPaneLinkList.Erase(currIt);
		Layout::FreeMemory(&(*currIt));
	}
}

void Group::AppendPane(Pane *pPane)
{
	if (void *pMem = Layout::AllocMemory(sizeof(detail::PaneLink)))
	{
		detail::PaneLink *pPaneLink = new (pMem) detail::PaneLink();

		pPaneLink->mTarget = pPane;
		mPaneLinkList.PushBack(pPaneLink);
	}
}

GroupContainer::~GroupContainer()
{
	NW4HBM_RANGE_FOR_NO_AUTO_INC(it, mGroupList)
	{
		decltype(it) currIt = it++;

		mGroupList.Erase(currIt);

		if (!currIt->IsUserAllocated())
		{
			currIt->~Group();
			Layout::FreeMemory(&(*currIt));
		}
	}
}

void GroupContainer::AppendGroup(Group *pGroup)
{
	mGroupList.PushBack(pGroup);
}

Group *GroupContainer::FindGroupByName(const char *findName)
{
	NW4HBM_RANGE_FOR(it, mGroupList)
	{
		if (detail::EqualsPaneName(it->GetName(), findName))
			return &(*it);
	}

	return nullptr;
}

}} // namespace nw4hbm::lyt
