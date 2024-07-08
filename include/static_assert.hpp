#define STATIC_ASSERT(expr) \
    typedef char static_assert[expr ? 1 : -1];

#define ASSERT_SIZE(t, size) STATIC_ASSERT(sizeof(t) == size)