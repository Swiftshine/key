#include "ut_LinkList.hpp"

/*******************************************************************************
 * headers
 */

#include <types.h> // nullptr

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut { namespace detail {

LinkListImpl::~LinkListImpl()
{
	Clear();
}

LinkListImpl::Iterator LinkListImpl::Erase(Iterator it)
{
	Iterator itNext(it);
	++itNext;

	return Erase(it, itNext);
}

LinkListImpl::Iterator LinkListImpl::Erase(LinkListImpl::Iterator itFirst,
                                           LinkListImpl::Iterator itLast)
{
	LinkListNode *pIt = itFirst.mPointer, *pItLast = itLast.mPointer, *pNext;

	while (pIt != pItLast)
	{
		pNext = pIt->mNext;
		Erase(pIt);
		pIt = pNext;
	}

	return itLast;
}

void LinkListImpl::Clear()
{
	Erase(GetBeginIter(), GetEndIter());
}

LinkListImpl::Iterator LinkListImpl::Insert(Iterator it, LinkListNode *p)
{
	LinkListNode *pIt = it.mPointer;
	// why are there two lines between these?

	LinkListNode *pItPrev = pIt->mPrev;

	p->mNext = pIt;
	p->mPrev = pItPrev;

	pIt->mPrev = p;
	pItPrev->mNext = p;

	mSize++;

	return p;
}

LinkListImpl::Iterator LinkListImpl::Erase(LinkListNode *p)
{
	LinkListNode *pNext = p->mNext, *pPrev = p->mPrev;

	pNext->mPrev = pPrev;
	pPrev->mNext = pNext;

	mSize--;

	p->mNext = nullptr;
	p->mPrev = nullptr;

	return pNext;
}

}}} // namespace nw4hbm::ut::detail
