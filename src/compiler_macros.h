#ifndef COMPILER_MACROS_H
#define COMPILER_MACROS_H

#ifndef __MWERKS__
#define __option(x)
#define __declspec(x)
#define __attribute__(x)
#endif

#define STR_(x)					#x
#define STR(x)					STR_(x)
#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)

#define ALIGN(x) __attribute__((aligned(x)))

// There are two attributes for this for whatever reason
// The __attribute__ didn't work on ec::malloc(), the __declspec errors on class methods
// Just try both and see which works lol
#define DONT_INLINE __declspec(noinline) // use for regular functions
#define DECOMP_DONT_INLINE __attribute__((never_inline))
#define DONT_INLINE_CLASS __attribute__((never_inline)) // use for class methods

#define DECOMP_FORCEACTIVE(module, ...)                                        \
    void fake_function(...);                                                   \
    void CAT(FORCEACTIVE##module, __LINE__)(void);                          \
    void CAT(FORCEACTIVE##module, __LINE__)(void) {                         \
        fake_function(__VA_ARGS__);                                            \
    }

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#define ATTR_UNUSED __attribute__((unused))
#define ATTR_WEAK __attribute__((weak))

#endif
