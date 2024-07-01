#define STATIC_ASSERT(expr) \
    typedef char static_assert[expr ? 1 : -1];
