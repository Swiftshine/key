#include "lyt_bounding.hpp"

/*******************************************************************************
 * headers
 */

#include "lyt_common.hpp"
#include "lyt_drawInfo.hpp"
#include "lyt_pane.hpp"

#include "../ut/ut_Color.hpp"
#include "../ut/ut_RuntimeTypeInfo.hpp"

/*******************************************************************************
 * variables
 */

namespace nw4hbm { namespace lyt
{
	const ut::detail::RuntimeTypeInfo Bounding::typeInfo(&Pane::typeInfo);
}} // namespace nw4hbm::lyt

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace lyt {

Bounding::Bounding(const res::Bounding *pBlock, const ResBlockSet &):
	Pane(pBlock)
{}

Bounding::~Bounding() {}

void Bounding::DrawSelf(const DrawInfo &drawInfo)
{
	if (drawInfo.IsDebugDrawMode())
	{
		LoadMtx(drawInfo);
		detail::DrawLine(GetVtxPos(), mSize, ut::Color(0x00ff00ff));
	}
}

}} // namespace nw4hbm::lyt
