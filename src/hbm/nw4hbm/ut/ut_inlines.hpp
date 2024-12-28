#ifndef RVL_SDK_HBM_NW4HBM_UT_INLINES_HPP
#define RVL_SDK_HBM_NW4HBM_UT_INLINES_HPP

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut { namespace
{
	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x475f53, 0x4851db...
	class NonCopyable
	{
	// methods
	public:
		// cdtors
		NonCopyable() {}
		~NonCopyable() {}

	// deleted methods
	private:
		NonCopyable(const NonCopyable &);
		NonCopyable &operator =(const NonCopyable &);
	}; // size 0x01 (0x00 for inheritance)

	template <typename T>
	inline T Min(T a, T b)
	{
		return a > b ? b : a;
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return a < b ? b : a;
	}
}}} // namespace nw4hbm::ut::(unnamed)

#endif // RVL_SDK_HBM_NW4HBM_UT_INLINES_HPP
