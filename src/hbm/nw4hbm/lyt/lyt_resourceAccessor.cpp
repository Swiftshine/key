#include "lyt_resourceAccessor.hpp"

/*******************************************************************************
 * functions
 */

// forward declarations
namespace nw4hbm { namespace ut { class Font; }}

// these guys were on something when they decided to make this file

namespace nw4hbm { namespace lyt {

// destructor is first for some reason
ResourceAccessor::~ResourceAccessor() {}

ResourceAccessor::ResourceAccessor() {}

ut::Font *ResourceAccessor::GetFont(const char *)
{
	return nullptr;
}

}} // namespace nw4hbm::lyt
