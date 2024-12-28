#include "ut_list.hpp"

/*******************************************************************************
 * headers
 */

#include <types.h>

/*******************************************************************************
 * macros
 */

#define OBJ_TO_NODE(list_, object_)	\
	reinterpret_cast<Link *>(reinterpret_cast<u32>(object_) + (list_)->offset)

/*******************************************************************************
 * local function declarations
 */

namespace nw4hbm { namespace ut
{
	static void SetFirstObject(List *list, void *object);
}} // namespace nw4hbm::ut

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut {

void List_Init(List *list, u16 offset)
{
	list->headObject = nullptr;
	list->tailObject = nullptr;

	list->numObjects = 0;

	list->offset = offset;
}

static void SetFirstObject(List *list, void *object)
{
	Link *link = OBJ_TO_NODE(list, object);

	link->nextObject = nullptr;
	link->prevObject = nullptr;

	list->headObject = object;
	list->tailObject = object;

	list->numObjects++;
}

void List_Append(List *list, void *object)
{
	if (!list->headObject)
	{
		return SetFirstObject(list, object);
	}
	else
	{
		Link *link = OBJ_TO_NODE(list, object);

		link->prevObject = list->tailObject;
		link->nextObject = nullptr;

		OBJ_TO_NODE(list, list->tailObject)->nextObject = object;

		list->tailObject = object;
		list->numObjects++;
	}
}

void List_Remove(List *list, void *object)
{
	Link *link = OBJ_TO_NODE(list, object);

	if (!link->prevObject)
		list->headObject = link->nextObject;
	else
		OBJ_TO_NODE(list, link->prevObject)->nextObject = link->nextObject;

	if (!link->nextObject)
		list->tailObject = link->prevObject;
	else
		OBJ_TO_NODE(list, link->nextObject)->prevObject = link->prevObject;

	link->prevObject = nullptr;
	link->nextObject = nullptr;

	list->numObjects--;
}

void *List_GetNext(const List *list, const void *object)
{
	if (object == nullptr)
		return list->headObject;

	return OBJ_TO_NODE(list, object)->nextObject;
}

void *List_GetNth(const List *list, u16 index)
{
	int count = 0;
	Link *object = nullptr;

	for (; (object = static_cast<Link *>(List_GetNext(list, object))); count++)
	{
		if (index == count)
			return object;
	}

	return nullptr;
}

}} // namespace nw4hbm::ut
